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
#include <gpiorw/gpiorw.h>

using namespace ConfigInfo;

namespace Driver
{
    class PWM
    {
    public:
        PWM(sGpioCtrl* gpi0_list, int count)
        :bRunning(false)
        ,gpioCount(0)
        ,pwm_freq(100)
        ,speed(0)
        ,enable_time(0)
        ,disable_time(0)
        ,tObj(nullptr)
        {
            gpioCount = std::min(count,MAX_GPIO_PINS);
            memset(ctrls, 0, sizeof(ctrls));
            memcpy(ctrls, gpio_list, sizeof(sGpioCtrl)*gpioCount);
        }
        virtual ~PWM()
        {
            stop();
        }

        void start()
        {
            stop();
            tObj = new std::thread(tPWMGen)
        }
        void stop()
        {
            bRunning = false;
            if(tObj)
            {
                tObj->join();
                delete tObj;
                tObj = nullptr;
            }
        }

        void setSpeed(unsigned int speed)
        {
            if(speed>100) speed = 100;

            this->speed = speed;

            // calculate plus width, unit: ms
            float plus_width = 1000 / pwm_freq; // ms

            // calculate enable time
            this->enable_time = plus_width * (speed/100.0);

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
        int pwm_freq;

        int gpioCount;
        sGpioCtrl ctrls[MAX_GPIO_PINS];
        std::thread* tObj; 
        std::atomic<int> enable_time; 
        std::atomic<int> disable_time; 
    protected:
        void tPWMGen()
        {
            float plus_width = 1000.0 / pwm_freq;   // ms

            bRunning = true;
            while(bRunning)
            {
                if(speed==0)
                {
                    gpio_disable();
                    std::this_thread::sleep_for(200ms);
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
            for(int i=0; i<gpioCount; i++)
            {
                GPIORW::GPIOWrite(ctrls[i].pin, ctrls[i].value);
            }
        }
        void gpio_disable()
        {
            for(int i=0; i<gpioCount; i++)
            {
                GPIORW::GPIOWrite(ctrls[i].pin, 0);
            }
        }
    };
    

} // namespace Driver

#endif //!PWM_HPP_