
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
        *    Get type of this executive device
        *
        *  @return
        *    Type of the device
        */
        virtual ExecutiveDeviceType getType() = 0;
        
        /**
        *  @brief
        *    Check to make sure wether the device is avaliable.
        *
        *  @return
        *    'true' will be returned if this device is avaliable.
        */
        virtual bool avaliable() = 0;
        
        /**
        *  @brief
        *    Reset to initial state
        */
        virtual void reset() = 0;

        /**
        *  @brief
        *    Do work
        *
        *  @return
        *    Code of running result
        */
        virtual unsigned int execute(MoveType moveType, MoveSpeed speed) = 0;
    };

} // namespace WalkDriver
