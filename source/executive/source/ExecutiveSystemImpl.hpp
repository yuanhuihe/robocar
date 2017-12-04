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

        virtual ExecutiveBody* enumFirstExecutiveBody()
        {
            unloadCfg();

            // read action config
            std::string file = get_curr_dir() + "executive.xml";
            std::cout << file << std::endl;
            loadCfg(file);

            enumPos = 0;
            if(executiveBodys.size()>0)
            {
                return executiveBodys[0];
            }
            
            return nullptr;
        }

        virtual ExecutiveBody* enumNextExecutiveBody()
        {
            enumPos++;
            if(executiveBodys.size()>enumPos)
            {
                return executiveBodys[enumPos];
            }
            
            return nullptr;
        }

    private:
        ConfigInfo::config cfg;
        std::vector<ConfigInfo::sExecutiveBody> sbodies;
        std::vector<ExecutiveBody*> executiveBodys;
        int enumPos;

        void loadCfg(std::string file)
        {
            // losf xml
            cfg.load_xml(file);

            // get actions
            cfg.get_executive_bodies(sbodies);
            for(auto bd : sbodies)
            {
                executiveBodys.push_back(new ExecutiveBodymImpl(bd));
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

            // clear config data
            enumPos = 0;
            sbodies.clear();
        }
    };

} // namespace Driver

#endif //!EXECUTIVESYSTEMIMPL_HPP_