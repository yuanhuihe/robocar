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
    // Execution error types
#define EET_OK                      0   // No error
#define EET_UnknownAction           1   // Unknown moving command
#define EET_ActionNotSupport        2   // Not supported moving command
#define EET_SpeedOutOfRange         3   // 

#define PWM_FREQ                    100 // Hz


    enum ExecutiveType
    {
        ET_Unknown = 0,
        ET_Motor,
    };

} // namespace Driver

#endif //!EXECUTIVE_DEF_H_