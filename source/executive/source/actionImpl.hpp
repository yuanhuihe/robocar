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
        :pwm(cfgAct.ctrls, cfgAct.ctrl_count)
        {
            cfg = cfgAct;
        }
        virtual ~ActionImpl()
        {
            if(pwm.isRunning())
            {
                standby();
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
        
        virtual void standby()
        {
            execute(0);
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

            return EET_OK;
        }

    protected:
        sActionConfig cfg;
        PWM pwm;
    };
    

} // namespace Driver

#endif //!ACTION_IMPL_HPP_
