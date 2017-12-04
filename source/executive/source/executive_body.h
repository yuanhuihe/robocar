/**
* @brief
*   Executive aciton interface file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.11.22
*/
#ifndef EXECUTIVE_BODY_H_
#define EXECUTIVE_BODY_H_

#include <executive/executive_api.h>
#include <executive/executive_def.h>
#include <executive/action.h>

namespace Driver
{
    /**
    *  @brief
    *    Executive body interface
    */
    class EXECUTIVE_API ExecutiveBody
    {
    public:
        /**
        *  @brief
        *    Constructor
        */
        ExecutiveBody();

        /**
        *  @brief
        *    Destructor
        */
        virtual ~ExecutiveBody();
        
        /**
        *  @brief
        *    Get type of executive body
        *
        *  @return
        *    Type of the executive body
        */
        virtual ExecutiveType getType() = 0;
        
        /**
        *  @brief
        *    Get executive body name
        *
        *  @return
        *    Name of this body
        */
        virtual char* getName() = 0;
        
        /**
        *  @brief
        *    Enum first action this executive body can excuting
        *
        *  @return
        *    Action object, return nullptr if no action can be used.
        */
        virtual Action* enumFirstAction() = 0;

        /**
        *  @brief
        *    Enum all actions this executive body can excuting
        *
        *  @return
        *    Action object, return nullptr if no more action.
        */
        virtual Action* enumNextAction() = 0;

        /**
        *  @brief
        *    Execute an action
        *
        *  @return
        *    Code of running result
        */
        virtual unsigned int execute(Action* action, unsigned int speed) = 0;
        
        /**
        *  @brief
        *    Stop execution
        *
        */
        virtual void stop() = 0;
    };

} // namespace Driver

#endif //!EXECUTIVE_BODY_H_