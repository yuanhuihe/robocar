/**
* @brief
*   Executive system implimentation file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef EXECUTIVE_BODY_IMPL_HPP_
#define EXECUTIVE_BODY_IMPL_HPP_

#include "executive_body.h"
#include "actionImpl.hpp"
#include "configxml.h"
#include "_inl.hpp"
#include "_utility.hpp"
#include "pwm.hpp"

namespace Driver
{
    class ExecutiveBodymImpl : public ExecutiveBody
    {
    public:
        ExecutiveBodymImpl(sExecutiveBody bd)
            : bd(bd)
            , enumPos(0)
        {
        }
        virtual ~ExecutiveBodymImpl()
        {
            clear_acts();
        }
        
        virtual ExecutiveType getType()
        {
            return (ExecutiveType)bd.type;
        }
        
        virtual char* getName()
        {
            return bd.name;
        }
        
        virtual Action* enumFirstAction()
        {
            enumPos = 0;
            
            clear_acts();

            for(auto act : bd.acts)
            {
                Actions.push_back(new ActionImpl(act));
            }

            if(Actions.size()>0)
            {
                return Actions[0];
            }
            
            return nullptr;
        }

        virtual Action* enumNextAction()
        {
            enumPos++;
            if(Actions.size()>enumPos)
            {
                return Actions[enumPos];
            }
            
            return nullptr;
        }

        virtual unsigned int execute(Action* action, unsigned int speed)
        {
            if(action->getExecuteBodyID()!=bd.id) return EET_ActionNotSupport;

            if(!pwm.isRunning())
            {
                pwm.start();    
            }

            pwm.setSpeed(speed);

            return EET_OK;
        }
        
        virtual void updateExecuteSpeed(int speed)
        {
            pwm.setSpeed(speed);
        }
        
        virtual void stop()
        {
            pwm.stop();
        }

    private:
        sExecutiveBody bd;
        std::vector<Action*> Actions;
        int enumPos;

        PWM pwm;

        void clear_acts()
        {
            for(Action*& act : Actions)
            {
                delete act;
                act = nullptr;
            }
        }
    };

} // namespace Driver

#endif //!EXECUTIVE_BODY_IMPL_HPP_