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
#ifndef EXECUTIVESYSTEMIMPL_HPP_
#define EXECUTIVESYSTEMIMPL_HPP_

#include <executive/executive.h>
#include "executive_body_impl.hpp"
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
        
        virtual void loadSystem()
        {
            // clear config
            unloadCfg();

            // read action config
            std::string file = get_curr_dir() + "executive.xml";
            loadCfg(file);
        }
        
        virtual void unloadSystem()
        {
            // clear config
            unloadCfg();
        }

        virtual Action* enumFirstAction()
        {
            // clear config
            unloadCfg();

            // read action config
            std::string file = get_curr_dir() + CFG_EXECUTIVE_FILE;
            loadCfg(file);

            enumPos = 0;
            if(actions.size()>0)
            {
                return actions[0];
            }
            
            return nullptr;
        }

        virtual Action* enumNextAction()
        {
            enumPos++;
            if(actions.size()>enumPos)
            {
                return actions[enumPos];
            }
            
            return nullptr;
        }

        virtual bool runAction(Action* action, unsigned int speed)
        {
            if(action == nullptr) return false;
            
            Action* act = dynamic_cast<Action*>(action);
            if(act==nullptr) return false;

            int pid = action->getExecuteBodyID();
            if(executiveBodys.size()>pid)
            {
                return executiveBodys[pid]->execute(action, speed) == EET_OK;
            }
            return false;
        }

        virtual bool stopAction(Action* action)
        {
            if(action == nullptr) return false;
            
            Action* act = dynamic_cast<Action*>(action);
            if(act==nullptr) return false;

            int pid = action->getExecuteBodyID();
            if(executiveBodys.size()>pid)
            {
                executiveBodys[pid]->stop();
                return true;
            }
            return false;
        }

        virtual void resetSystem()
        {
            for (auto e : executiveBodys)
            {
                e->reset();
            }
        }
    private:
        ConfigInfo::config cfg;
        std::vector<ConfigInfo::sExecutiveBody> sbodies;
        std::vector<ExecutiveBody*> executiveBodys;
        std::vector<Action*> actions;
        int enumPos;

        void loadCfg(std::string file)
        {
            // losf xml
            cfg.load_xml(file);

            // get actions
            cfg.get_executive_bodies(sbodies);
            for(auto bd : sbodies)
            {
                ExecutiveBody* body = new ExecutiveBodymImpl(bd);
                executiveBodys.push_back(body);

                Action* act = body->enumFirstAction();
                while(act)
                {
                    actions.push_back(act);
                    act = body->enumNextAction();
                }
            }
        }

        void unloadCfg()
        {
            // firstly reset system
            for(auto& bd: executiveBodys)
            {
                bd->stop();
                delete bd;
                bd = nullptr;
            }
            executiveBodys.clear();

            actions.clear();

            // clear config data
            enumPos = 0;
            sbodies.clear();
        }
    };

} // namespace Driver

#endif //!EXECUTIVESYSTEMIMPL_HPP_