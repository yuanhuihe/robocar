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
        PWM(sSpeedCtrl sc)
        :bRunning(false)
        ,speed_data(sc)
        ,tObj(nullptr)
        ,enable_time(0)
        ,disable_time(0)
        {
            // calculate plus width, unit: ms
            plus_width = 1000 / PWM_FREQ; // ms
            speed_span = speed_data.range_max - speed_data.range_min;
            assert(speed_span>0);
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
            // DON'T STOP IMMEDIATELY!
            int stop_steps = 5;
            while(stop_steps>0 && this->speed>0)
            {
                unsigned int s = this->speed * (2.0/3.0);
                setSpeed(s);

                std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(500));

                stop_steps--;
            }

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
            // assert(speed_span>0)
            if(speed_span<=0) return;

            // correct speed
            if(s>speed_data.range_max) s = speed_data.range_max;
            if(s<speed_data.range_min) s = speed_data.range_min;

            // save speed
            this->speed = s;

            // calculate enable time
            this->enable_time = plus_width * ((float)speed/speed_span);

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
        sSpeedCtrl speed_data;
        int speed_span;
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