
#pragma once


#include <walkdriver/walkdriver_api.h>
#include <walkdriver/walkdriver_def.h>
#include <walkdriver/executivedevice.h>


namespace WalkDriver
{
    /**
    *  @brief
    *    Implement walk commands to driving wheels
    */
    class WALKDRIVER_API WalkSystem
    {
    public:
        /**
        *  @brief
        *    Constructor
        */
        WalkSystem();

        /**
        *  @brief
        *    Destructor
        */
        virtual ~WalkSystem();

        /**
        *  @brief
        *    Initialze and return the driver system object if initialized successfully. Other wise return null.
        *
        *  @param[in] chassisType
        *    Tpye of walk system.
        *
        *  @return
        *    Object of the driver system
        */
        static WalkSystem* InitSystem(ChassisType chassisType);

        /**
        *  @brief
        *    Release the WalkSystem object
        *
        *  @param[in] obj
        *    Address of pointer of WalkSystem object.
        *
        *  @return
        *    Value of the i'th fibonacci number
        */
        static void ReleaseSystem(WalkSystem** obj);

        /**
        *  @brief
        *    Enum all executive bodies
        *
        *  @return
        *    Found executive device
        */
        virtual ExecutiveDevice* enumExecutiveBody() = 0;
    };


} // namespace WalkDriver
