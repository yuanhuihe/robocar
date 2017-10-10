
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
    private:
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

    public:

        /**
        *  @brief
        *    Initialze and return the driver system object if initialized successfully. Other wise return null.
        *
        *  @return
        *    Object of the driver system
        */
        static WalkSystem* InitSystem();

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
        *  @param[in] i
        *    Index
        *
        *  @return
        *    Value of the i'th fibonacci number
        */
        ExecutiveDevice* enumExecutiveBody();
    };


} // namespace WalkDriver
