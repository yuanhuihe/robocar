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
        *    @ref ExecutiveBody object
        */
        virtual Action* enumFirstAction() = 0;
        virtual Action* enumNextAction() = 0;

        /**
        *  @brief
        *    Reset system to standby state.
        */
        virtual void resetSystem() = 0;

        /**
        *  @brief
        *    Run an action, or update speed of an running action.
        *  @param
        *   [in] action, an action will be executed by the system.
        *   [in] speed, refered speed of action. '0' means stop execute this action.
        *
        *  @return
        *    Execution code, '0' means successful. An xecution error code is defined in 'executive_def.h' file.
        */
        virtual unsigned int runAction(Action* action, unsigned int speed) = 0;

        /**
        *  @brief
        *    Stop an action
        *  @param
        *   [in] action, an action will be stoped.
        *
        *  @return
        *    Execution code, '0' means successful. An xecution error code is defined in 'executive_def.h' file.
        */
        virtual unsigned int stopAction(Action* action) = 0;
    };


} // namespace Driver

#endif //!EXECUTIVE_H_