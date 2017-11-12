
#pragma once

#include <executive/executive.h>
#include "actionImpl.hpp"
#include "configxml.h"
#include "_inl.hpp"
#include "_utility.hpp"

namespace Driver
{
    class ExecutiveSystemImpl : public ExecutiveSystem
    {
    public:
        ExecutiveSystemImpl()
            : cfg(ConfigInfo::DRIVER_ACTION)
            , enumPos(0)
        {
        }
        virtual ~ExecutiveSystemImpl()
        {

        }

        virtual Action* enumFirstAction()
        {
            enumPos = 0;
            cfgActions.clear();

            for(auto& act: Actions)
            {
                ActionType type = act->getType();
                if(type)
                {
                    act->execute(0);
                }
                delete act;
                act = nullptr;
            }
            Actions.clear();

            std::string file = get_curr_dir() + "executive.xml";
            std::cout << file << std::endl;
            cfg.load_xml(file);
            cfg.get_actions(cfgActions);
            for(auto act : cfgActions)
            {
                cfgActions[enumPos];
                Action* action = new ActionImpl();
                Actions.push_back(action);
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
            if(cfgActions.size()>enumPos)
            {
                return Actions[enumPos];
            }
            
            return nullptr;
        }

    private:
        ConfigInfo::config cfg;
        std::vector<ConfigInfo::sActionConfig> cfgActions;
        std::vector<Action*> Actions;
        int enumPos;
    };

} // namespace Driver
