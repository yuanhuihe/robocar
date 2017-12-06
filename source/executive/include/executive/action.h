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
        *    Get action
        *
        *  @return
        *    Name of this action
        */
        virtual char* getName() = 0;
        
        /**
        *  @brief
        *    Get id of ExecuteBody this action belong to
        *
        *  @return
        *    Id of ExecuteBody
        */
        virtual int getExecuteBodyID() = 0;
    };

} // namespace Driver

#endif //!ACTION_H_