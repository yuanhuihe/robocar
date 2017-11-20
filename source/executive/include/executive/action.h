/**
* @brief
*   Executive aciton interface file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.11.12
*/
#ifndef ACTION_H_
#define ACTION_H_

#include <executive/executive_api.h>
#include <executive/executive_def.h>

namespace Driver
{
    /**
    *  @brief
    *    Action interface
    */
    class EXECUTIVE_API Action
    {
    public:
        /**
        *  @brief
        *    Constructor
        */
        Action();

        /**
        *  @brief
        *    Destructor
        */
        virtual ~Action();
        
        /**
        *  @brief
        *    Get type of action
        *
        *  @return
        *    Type of the device
        */
        virtual ActionType getType() = 0;
        
        /**
        *  @brief
        *    Get action
        *
        *  @return
        *    Name of this action
        */
        virtual char* getName() = 0;
        
        /**
        *  @brief
        *    Wether this action has speed controlling
        *
        */
        virtual sSpeedCtrl getSpeed() = 0;
        
        /**
        *  @brief
        *    Do work
        *
        *  @return
        *    Code of running result
        */
        virtual unsigned int execute(int speed) = 0;
        
        /**
        *  @brief
        *    Stop execution
        *
        */
        virtual void stop() = 0;
    };

} // namespace Driver

#endif //!ACTION_H_