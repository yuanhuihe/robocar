/**
* @brief
*   PWM generation implimentation file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.11.18
*/
#ifndef PWM_HPP_
#define PWM_HPP_

#include <atomic>
#include <chrono>
#include <thread>
#include <assert.h>
#include <string.h>
#include <gpiorw/gpiorw.h>
#include "executive/executive_def.h"

using namespace ConfigInfo;

namespace Driver
{
    class PWM
    {
    public:
        PWM(sSpeedCtrl sd, sGpioCtrl* gpio_list, int count)
        :bRunning(false)
        ,speed(0)
        ,gpio_cunt(0)
        ,tObj(nullptr)
        ,enable_time(0)
        ,disable_time(0)
        {
            gpio_cunt = std::min(count,MAX_GPIO_PINS);
            memset(ctrls, 0, sizeof(ctrls));
            memcpy(ctrls, gpio_list, sizeof(sGpioCtrl)*gpio_cunt);
            memcpy(&speedData, &sd, sizeof(speedData));

            speed = sd.default_value;

            // calculate plus width, unit: ms
            plus_width = 1000 / PWM_FREQ; // ms
        }
        virtual ~PWM()
        {
            stop();
        }

        void start()
        {
            stop();
            tObj = new std::thread(&PWM::tPWMGen, this);
        }
        void stop()
        {
            // stop pwm generator thread
            bRunning = false;
            if(tObj)
            {
                tObj->join();
                delete tObj;
                tObj = nullptr;
            }

            // reset gpio
            gpio_disable();
        }

        void setSpeed(unsigned int s)
        {
            if(s>speedData.range_max) s = speedData.range_max;
            if(s<speedData.range_min) s = speedData.range_min;

            this->speed = s;

            // calculate enable time
            int range = speedData.range_max - speedData.range_min;
            assert(range>0);

            this->enable_time = plus_width * ((float)speed/range);

            // calculate disable time
            this->disable_time = plus_width - enable_time;
        }

        unsigned int getSpeed()
        {
            return speed;
        }

        bool isRunning()
        {
            return bRunning;
        }

    protected:
        bool bRunning;
        int speed;

        int gpio_cunt;
        sGpioCtrl ctrls[MAX_GPIO_PINS];
        sSpeedCtrl speedData;
        float plus_width;
        std::thread* tObj; 
        std::atomic<int> enable_time; 
        std::atomic<int> disable_time; 
    protected:
        void tPWMGen()
        {
            bRunning = true;
            while(bRunning)
            {
                if(speed==0)
                {
                    gpio_disable();
                    std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));
                    continue;
                }
            
                // part of plus payload space
                gpio_enable();
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(enable_time));

                // part of plus of free space 
                gpio_disable();
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(disable_time));
            }
        }
        void gpio_enable()
        {
            for(int i=0; i<gpio_cunt; i++)
            {
                GPIORW::GPIOWrite(ctrls[i].pin, ctrls[i].value);
            }
        }
        void gpio_disable()
        {
            for(int i=0; i<gpio_cunt; i++)
            {
                GPIORW::GPIOWrite(ctrls[i].pin, 0);
            }
        }
    };
    

} // namespace Driver

#endif //!PWM_HPP_