/**
* @brief
*   Executive interface definitions file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef EXECUTIVE_DEF_H_
#define EXECUTIVE_DEF_H_

namespace Driver
{
    // Execute error types
#define EET_OK                      0   // No error
#define EET_UnknownAction           1   // Unknown moving command
#define EET_ActionNotSupport        2   // Not supported moving command
#define EET_SpeedOutOfRange         3   // 

#define PWM_FREQ                    100 // Hz


    // Moving type
    enum ActionType
    {
        AT_Unknown = 0,
        AT_Ready,
        AT_MoveForward,
        AT_MoveBackward,
        AT_Leftward,
        AT_Rightward,
        AT_BackLeft,
        AT_BackRigh,
        AT_HeadNod,
        AT_HeadShook,
    };


    typedef struct _sSpeedCtrl
    {
        bool has_speed;
        int range_min;
        int range_max;
        int default_value;
    }sSpeedCtrl;



} // namespace Driver

#endif //!EXECUTIVE_DEF_H_