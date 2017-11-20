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
        
        virtual void loadSystem()
        {
            unloadCfg();

            // read action config
            std::string file = get_curr_dir() + "executive.xml";
            std::cout << file << std::endl;
            loadCfg(file);
        }
        
        virtual void unloadSystem()
        {
            unloadCfg();
        }

        virtual Action* enumFirstAction()
        {
            unloadCfg();

            // read action config
            std::string file = get_curr_dir() + "executive.xml";
            std::cout << file << std::endl;
            loadCfg(file);

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

        void loadCfg(std::string file)
        {
            // losf xml
            cfg.load_xml(file);

            // get actions
            cfg.get_actions(cfgActions);
            for(auto act : cfgActions)
            {
                Action* action = new ActionImpl(act);
                Actions.push_back(action);
            }
        }

        void unloadCfg()
        {
            // firstly reset system
            for(auto& act: Actions)
            {
                act->stop();
                
                delete act;
                act = nullptr;
            }
            Actions.clear();

            // clear config data
            enumPos = 0;
            cfgActions.clear();
        }
    };

} // namespace Driver

#endif //!EXECUTIVESYSTEMIMPL_HPP_