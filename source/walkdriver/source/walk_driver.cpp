
#include <walkdriver/walkdriver.h>
#include <fsgpio/fsgpio.h>
#include "motor_system.hpp"
#include "foot_walksystem.hpp"
#include <tuple>
#include <string>

namespace WalkDriver
{
    WalkSystem* g_walkSys = nullptr;

    WalkSystem::WalkSystem()
    {
        FSGPIO::GPIOLibInit();
    }

    WalkSystem::~WalkSystem()
    {
        FSGPIO::GPIOLibRelease();
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
