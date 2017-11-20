/**
* @brief
*   Action implimentation file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef ACTION_IMPL_HPP_
#define ACTION_IMPL_HPP_

#include <executive/executive.h>
#include "configdef.hpp"
#include <gpiorw/gpiorw.h>
#include "pwm.hpp"

using namespace ConfigInfo;

namespace Driver
{
    class ActionImpl: public Action
    {
    public:
        ActionImpl(sActionConfig cfgAct)
        :pwm(cfgAct.speed, cfgAct.ctrls, cfgAct.ctrl_count)
        {
            cfg = cfgAct;
        }
        virtual ~ActionImpl()
        {
            stop();
        }

        virtual ActionType getType()
        {
            return (ActionType)cfg.type;
        }

        virtual char* getName()
        {
            return cfg.name;
        }
        
        virtual sSpeedCtrl getSpeed() 
        {
            return cfg.speed;
        }
        
        virtual unsigned int execute(int speed)
        {
            if (speed < cfg.speed.range_min || speed>cfg.speed.range_max)
            {
                return EET_SpeedOutOfRange;
            }

            if(!pwm.isRunning())
            {
                pwm.start();    
            }

            pwm.setSpeed(speed);

            return EET_OK;
        }

        virtual void stop()
        {
            pwm.stop();
        }

    protected:
        sActionConfig cfg;
        PWM pwm;
    };
    

} // namespace Driver

#endif //!ACTION_IMPL_HPP_
