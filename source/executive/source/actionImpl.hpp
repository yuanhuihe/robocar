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
        :pwm(cfgAct.ctrls, cfgAct.gpioCount)
        {
            cfg = cfgAct;
        }
        virtual ~ActionImpl()
        {
            if(pwm.isRunning())
            {
                pwm.setSpeed(0);
                pwm.stop();
            }
        }

        virtual ActionType getType()
        {
            return (ActionType)cfg.type;
        }

        virtual char* getName()
        {
            return cfg.name;
        }
        
        virtual unsigned int execute(SpeedPercent speed)
        {
            if (speed < 0 || speed>100)
            {
                return EET_SpeedOutOfRange;
            }

            if(!pwm.isRunning())
            {
                pwm.start();    
            }

            pwm.setSpeed(speed);

            // for(int i=0; i< cfg.ctrl_count; i++)
            // {
            //     GPIORW::GPIOWrite(cfg.ctrls[i].pin, cfg.ctrls[i].value);
            // }
            return EET_OK;
        }

    protected:
        sActionConfig cfg;
        PWM pwm;
    };
    

} // namespace Driver

#endif //!ACTION_IMPL_HPP_
