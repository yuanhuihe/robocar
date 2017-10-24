
#pragma once

#include <walkdriver/walkdriver.h>
#include <walkdriver/walkdriver.h>

namespace WalkDriver
{
    class FootWalkSystem : public WalkSystem
    {
    public:
        FootWalkSystem()
        {

        }
        virtual ~FootWalkSystem()
        {

        }

        virtual ExecutiveDevice* enumFirstExecutiveBody()
        {

            return nullptr;
        }

        virtual ExecutiveDevice* enumNextExecutiveBody()
        {

            return nullptr;
        }

        virtual ExecutiveDevice* getExecutiveBody(ExecutiveDevicePartType ptype)
        {
            return nullptr;
        }

    private:

    };

} // namespace WalkDriver