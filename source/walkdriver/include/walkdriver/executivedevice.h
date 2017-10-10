
#pragma once

#include <walkdriver/walkdriver_api.h>
#include <walkdriver/walkdriver_def.h>

namespace WalkDriver
{
    /**
    *  @brief
    *    Executive device, such as DC motor, steering gear, stepper motor,
    */
    class WALKDRIVER_API ExecutiveDevice
    {
    public:
        /**
        *  @brief
        *    Constructor
        */
        ExecutiveDevice();

        /**
        *  @brief
        *    Destructor
        */
        virtual ~ExecutiveDevice();
        
        /**
        *  @brief
        *    Do work
        *
        *  @return
        *    Code of running result
        */
        virtual unsigned int execute() = 0;
    };

} // namespace WalkDriver
