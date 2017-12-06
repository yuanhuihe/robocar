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

        void run_action(int act_index, unsigned int speed)
        {
            if (act_index >= seb.act_count) return;

            if (curr_action.id != act_index)
            {
                // action will change, stop pre-action
                stop();

                // update as new action data
                std::lock_guard<std::mutex> l(curr_action_locker);
                curr_action = seb.acts[act_index];
            }

            // start pwm generation
            if (tObj == nullptr)
            {
                tObj = new std::thread(&PWM::tPWMGen, this);
            }

            // change speed
            change_speed_gradually(speed);
        }

        void stop()
        {
            // DON'T STOP IMMEDIATELY!
            change_speed_gradually(0);

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
        std::mutex curr_action_locker;
        sAction curr_action;
        std::atomic<int> curr_speed;

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
            std::lock_guard<std::mutex> l(curr_action_locker);

            for (int i = 0; i<action.ctrl_count; i++)
            {
                GPIORW::GPIOWrite(action.ctrls[i].pin, action.ctrls[i].value);
            }
        }
        void gpio_disable(sAction& action)
        {
            std::lock_guard<std::mutex> l(curr_action_locker);

            for (int i = 0; i<action.ctrl_count; i++)
            {
                GPIORW::GPIOWrite(action.ctrls[i].pin, 0);
            }
        }
        
        void change_speed_gradually(unsigned int speed)
        {
            // correct speed
            if (speed>seb.speed.range_max) speed = seb.speed.range_max;
            if (speed<seb.speed.range_min) speed = seb.speed.range_min;
            
            // total deta speed
            float deta_speed = (int)speed - curr_speed;
            if (abs(deta_speed) > 0)
            {
                // save current speed
                float tmp_curr_speed = curr_speed;

                // deta speed for every step
                int steps = 5;
                deta_speed /= steps;
                while (steps>0)
                {
                    tmp_curr_speed += deta_speed;

                    update_speed(tmp_curr_speed + 0.5);

                    std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));

                    steps--;
                }

                // set real time
                update_speed(speed);
            }
        }

        void update_speed(unsigned int speed)
        {
            // assert(speed_span>0)
            if (speed_span <= 0) return;

            // update speed
            this->curr_speed = speed;

            // calculate enable time
            this->enable_time = plus_width * ((float)curr_speed / speed_span);

            // calculate disable time
            this->disable_time = plus_width - enable_time;
        }
    };


} // namespace Driver

#endif //!PWM_HPP_