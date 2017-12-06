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
            , pwm(bd)
            , enumPos(0)
            , running_action_index(-1)
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

            for(int i=0; i<bd.act_count; i++)
            {
                Actions.push_back(new ActionImpl(bd.acts[i]));
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

        virtual void reset()
        {
            pwm.reset();
        }

        virtual unsigned int execute(Action* action, unsigned int speed)
        {
            ActionImpl* act = dynamic_cast<ActionImpl*>(action);
            if (act == nullptr)
            {
                return EET_UnknownAction;
            }

            if (act->getExecuteBodyID() != bd.id)
            {
                return EET_ActionNotSupport;
            }

            running_action_index = act->getId();
            pwm.run_action(running_action_index, speed);

            return EET_OK;
        }
        
        virtual void updateSpeed(int speed)
        {
            if (running_action_index >= 0)
            {
                pwm.run_action(running_action_index, speed);
            }
        }
        
        virtual void stop()
        {
            pwm.stop();
        }

    private:
        sExecutiveBody bd;
        std::vector<Action*> Actions;
        int running_action_index;
        int enumPos;

        PWM pwm;

        void clear_acts()
        {
            for(Action*& act : Actions)
            {
                delete act;
                act = nullptr;
            }
            Actions.clear();
        }
    };

} // namespace Driver

#endif //!EXECUTIVE_BODY_IMPL_HPP_