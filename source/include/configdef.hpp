#ifndef CONFIG_DEF_HPP_
#define CONFIG_DEF_HPP_

#include <string>
#include <vector>
#include <executive/executive_def.h>
using namespace Driver;

namespace ConfigInfo
{
#define NAME_VERSION    "ROBO_CAR"
#define HEAD_CFG        "config"
#define HEAD_EXE        "executive"
#define CFG_VERSION     "1.0"
#define EXE_VERSION     "1.0"
#define MAX_GPIO_PINS   40  // max gpio pins on raspberry PI
#define MAX_ACTION_CNT  10  // max actions a executive body can support

    enum xmlType_
    {
        APP_CONFIG,
        DRIVER_ACTION,
        UNTYPE
    };

    typedef struct _sSpeedCtrl
    {
        int range_min;
        int range_max;
        int default_value;
    }sSpeedCtrl;

    typedef struct _sGpioCtrl
    {
        int pin;
        int value;
    }sGpioCtrl;

    // Action configration
    typedef struct _sAction
    {
        int parent_id;
        int type;       // type, defined in 'executive_def.h' file
        char name[64];  // name
        int ctrl_count;
        sGpioCtrl ctrls[MAX_GPIO_PINS];
    }sAction;

    // Executive body configration
    typedef struct _sExecutiveBody
    {
        int id;
        int type;       // type, defined in 'executive_def.h' file
        char name[64];  // name
        int act_count;
        sAction acts[MAX_ACTION_CNT];
        sSpeedCtrl speed;
    }sExecutiveBody;

} // !namespace ConfigInfo
#endif // CONFIG_DEF_HPP_
