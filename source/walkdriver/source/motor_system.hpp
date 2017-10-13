
#pragma once

#include <walkdriver/walkdriver.h>
#include "configxml.h"
#include "_inl.hpp"
#include "_utility.hpp"

namespace WalkDriver
{
    class MotorSystem : public WalkSystem
    {
    public:
        MotorSystem()
            : cfg(xmlbus::WALK_SYSTEM)
        {
            std::string file = get_curr_dir() + "MotorSystem.xml";
            cfg.load_xml(file);

            // TBDTBDTBDTBDTBDTBDTBDTBDTBDTBD
            cfg.get_walk_device();
        }
        virtual ~MotorSystem()
        {

        }

        ExecutiveDevice* enumExecutiveBody()
        {

            return nullptr;
        }

    private:
        xmlbus::config cfg;
    };

} // namespace WalkDriver
