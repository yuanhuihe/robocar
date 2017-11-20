/**
* @brief
*   Executive interface file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef EXECUTIVE_H_
#define EXECUTIVE_H_

#include <executive/executive_api.h>
#include <executive/executive_def.h>
#include <executive/action.h>

namespace Driver
{
    /**
    *  @brief
    *    Implement exectivable body commands to driving execution system
    */
    class EXECUTIVE_API ExecutiveSystem
    {
    public:
        /**
        *  @brief
        *    Constructor
        */
        ExecutiveSystem();

        /**
        *  @brief
        *    Destructor
        */
        virtual ~ExecutiveSystem();

        /**
        *  @brief
        *    Initialze and return the driver system object if initialized successfully. Otherwise return null.
        *
        *  @return
        *    Object of the driver system
        */
        static ExecutiveSystem* InitSystem();

        /**
        *  @brief
        *    Release the system object
        *
        *  @param[in] obj
        *    Address of pointer of ExecutiveSystem object.
        */
        static void ReleaseSystem(ExecutiveSystem** obj);
        
        /**
        *  @brief
        *    Load and reset system to standby state
        *
        */
        virtual void loadSystem() = 0;
        
        /**
        *  @brief
        *    Unload system to release resources.
        *
        */
        virtual void unloadSystem() = 0;

        /**
        *  @brief
        *    Enum all actions this system can excuting
        *
        *  @return
        *    Action object
        */
        virtual Action* enumFirstAction() = 0;
        virtual Action* enumNextAction() = 0;
    };


} // namespace Driver

#endif //!EXECUTIVE_H_