
#include <walkdriver/walkdriver.h>
#include "motorsystem.hpp"
#include "footwalksystem.hpp"
#include <tuple>
#include <string>

namespace WalkDriver
{
    std::tuple<ChassisType, std::string> ChassisTypeMap[] = {
        { CT_MotorSystem,"MotorSystem.xml" },
        { CT_FootWalkSystem,"FootWalkSystem.xml" }
    };

    WalkSystem* g_walkSys = nullptr;

    WalkSystem::WalkSystem()
    {
    }

    WalkSystem::~WalkSystem()
    {
    }
    
    WalkSystem* WalkSystem::InitSystem(ChassisType chassisType)
    {
        if (g_walkSys == nullptr)
        {
            switch (chassisType)
            {
            case WalkDriver::CT_MotorSystem:
                g_walkSys = new MotorSystem();
                break;
            case WalkDriver::CT_FootWalkSystem:
                g_walkSys = new FootWalkSystem();
                break;
            case WalkDriver::CT_Unknown:
            default:
                break;
            }

            if (g_walkSys)
            {
                g_walkSys->enumExecutiveBody();
            }
        }
        return g_walkSys;
    }

    void WalkSystem::ReleaseSystem(WalkSystem** obj)
    {
        WalkSystem* tmp = dynamic_cast<WalkSystem*>(*obj);
        if (tmp)
        {
            delete tmp;
            *obj = nullptr;

            g_walkSys = nullptr;
        }
    }


} // namespace WalkDriver
