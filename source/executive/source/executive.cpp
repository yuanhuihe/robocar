
#include <executive/executive.h>

#include <tuple>
#include <string>
#include <gpiorw/gpiorw.h>
#include "ExecutiveSystemImpl.hpp"

namespace Driver
{
    ExecutiveSystem::ExecutiveSystem()
    {
        GPIORW::GPIOLibInit(GPIORW::GFT_WiringPi);
    }

    ExecutiveSystem::~ExecutiveSystem()
    {
        GPIORW::GPIOLibRelease();
    }
    
    ExecutiveSystem* ExecutiveSystem::InitSystem()
    {
        static ExecutiveSystem* sys = nullptr;
        if (sys == nullptr)
        {
            sys = new ExecutiveSystemImpl();
        }
        return sys;
    }

    void ExecutiveSystem::ReleaseSystem(ExecutiveSystem** obj)
    {
        ExecutiveSystem* tmp = dynamic_cast<ExecutiveSystem*>(*obj);
        if (tmp)
        {
            delete tmp;
            *obj = nullptr;
        }
    }


} // namespace Driver
