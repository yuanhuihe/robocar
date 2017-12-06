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
        PWM(sExecutiveBody bd)
            :bRunning(false)
            , seb(bd)
            , curr_speed(0)
            , tObj(nullptr)
            , enable_time(0)
            , disable_time(0)
        {
            // clear memory
            memset(&curr_action, 0, sizeof(curr_action));

            // calculate plus width, unit: ms
            plus_width = 1000 / PWM_FREQ;

            // calculate speed level range
            speed_span = seb.speed.range_max - seb.speed.range_min;
            assert(speed_span>0);
        }
        virtual ~PWM()
        {
            stop();
        }

        void run_action(int act_index)
        {
            if (act_index >= seb.act_count) return;

            curr_action = seb.acts[act_index];

            stop();
            tObj = new std::thread(&PWM::tPWMGen, this);
        }

        void stop()
        {
            // DON'T STOP IMMEDIATELY!
            int stop_steps = 5;
            while (stop_steps>0 && this->curr_speed>0)
            {
                unsigned int s = this->curr_speed * (2.0 / 3.0);
                setSpeed(s);

                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(500));

                stop_steps--;
            }

            // stop pwm generator thread
            bRunning = false;
            if (tObj)
            {
                tObj->join();
                delete tObj;
                tObj = nullptr;
            }

            // reset gpio
            gpio_disable(curr_action);
        }

        void setSpeed(unsigned int speed)
        {
            // assert(speed_span>0)
            if (speed_span <= 0) return;

            // correct speed
            if (speed>seb.speed.range_max) speed = seb.speed.range_max;
            if (speed<seb.speed.range_min) speed = seb.speed.range_min;

            // save speed
            this->curr_speed = speed;

            // calculate enable time
            this->enable_time = plus_width * ((float)curr_speed / speed_span);

            // calculate disable time
            this->disable_time = plus_width - enable_time;
        }

        unsigned int getSpeed()
        {
            return curr_speed;
        }

        bool isRunning()
        {
            return bRunning;
        }

        void reset()
        {
            // stop current action
            stop();

            // reset all gpio
            for (int i = 0; i < seb.act_count; i++)
            {
                sAction& act = seb.acts[i];
                for (int j = 0; j < act.ctrl_count; j++)
                {
                    GPIORW::GPIOWrite(act.ctrls[j].pin, 0);
                }
            }
        }

    protected:
        bool bRunning;
        sExecutiveBody seb;
        sAction curr_action;
        int curr_speed;

        int speed_span;
        float plus_width;
        std::thread* tObj;
        std::atomic<int> enable_time;
        std::atomic<int> disable_time;
    protected:
        void tPWMGen()
        {
            bRunning = true;
            while (bRunning)
            {
                if (curr_speed == 0)
                {
                    gpio_disable(curr_action);
                    std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));
                    continue;
                }

                // part of plus payload space
                gpio_enable(curr_action);
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(enable_time));

                // part of plus of free space 
                gpio_disable(curr_action);
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(disable_time));
            }
        }
        void gpio_enable(sAction& action)
        {
            for (int i = 0; i<action.ctrl_count; i++)
            {
                GPIORW::GPIOWrite(action.ctrls[i].pin, action.ctrls[i].value);
            }
        }
        void gpio_disable(sAction& action)
        {
            for (int i = 0; i<action.ctrl_count; i++)
            {
                GPIORW::GPIOWrite(action.ctrls[i].pin, 0);
            }
        }
    };


} // namespace Driver

#endif //!PWM_HPP_