
#pragma once

#include <walkdriver/walkdriver.h>
#include "configxml.h"
#include "_inl.hpp"
#include "_utility.hpp"
#include "dc_motor.hpp"

namespace WalkDriver
{
    class MotorSystem : public WalkSystem
    {
    public:
        MotorSystem()
            : cfg(xmlbus::WALK_SYSTEM)
        {
        }
        virtual ~MotorSystem()
        {

        }

        ExecutiveDevice* enumFirstExecutiveBody()
        {
            resetDevices();

            std::string file = get_curr_dir() + "MotorSystem.xml";
            cfg.load_xml(file);
            cfg.get_walk_device(sDevs);

            for(auto s: sDevs)
            {
                eDevs.push_back(new DCMotor(s));
            }

            if(eDevs.size()>0)
            {
                return eDevs[enumPos];
            }
            
            return nullptr;
        }

        ExecutiveDevice* enumNextExecutiveBody()
        {
            enumPos++;
            if(enumPos<eDevs.size())
            {
                return eDevs[enumPos];
            }
            else
            {
                return nullptr;
            }
        }

    private:
        xmlbus::config cfg;
        std::vector<DEV_INFO> sDevs;
        std::vector<ExecutiveDevice*> eDevs;
        int enumPos;

        void resetDevices()
        {
            enumPos = 0;
            while(eDevs.size()>0)
            {
                eDevs[0]->reset();
                delete eDevs[0];
                eDevs.erase(eDevs.begin());
            }
            
            sDevs.clear();
        }
    };

} // namespace WalkDriver
