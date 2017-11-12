#ifndef CONFIG_DEF_HPP_
#define CONFIG_DEF_HPP_

#include <string>
#include <vector>

namespace ConfigInfo
{
#define NAME_VERSION    "ROBO_CAR"
#define HEAD_CFG        "config"
#define HEAD_EXE        "executive"
#define CFG_VERSION     "1.0"
#define EXE_VERSION     "1.0"
#define MAX_GPIO_PINS   64

    enum xmlType_
    {
        APP_CONFIG,
        DRIVER_ACTION,
        UNTYPE
    };

    typedef struct _gpio_ctrl
    {
        int pin;
        int value;
    }gpio_ctrl;

    // Action configration
    typedef struct _sActionConfig
    {
        int type;       // ActionType, defined in 'executive_def.h' file
        char name[64];  // action name
        float speed_percent;
        int ctrl_count;
        gpio_ctrl ctrls[MAX_GPIO_PINS];
    }sActionConfig;

} // !namespace ConfigInfo
#endif // CONFIG_DEF_HPP_
