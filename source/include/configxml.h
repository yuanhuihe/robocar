#ifndef CONFIG_XML_H_
#define CONFIG_XML_H_

#include <string>

#include "global.hpp"
#include "xml_define.h"
#include "xml_parser.hpp"
#include "config_def.hpp"

namespace xmlbus
{

class config : public XML_Helper
{
public:
    config(xmlType_ type);
    ~config();

    // GET =========================================================================================
    CFG_BROKER get_broker_cfg();                                // get broker
    CFG_LICENSE get_license_cfg();                              // get license
    std::string get_language_cfg();                             // get language
    bool getConsoleStatus();                                    // get console status
    std::string getRootPath();                                  // get root path

    bool get_walk_device(std::vector<DEV_INFO>& devs);

    // SET =========================================================================================
    bool set_broker_cfg(CFG_BROKER& broker);                    // if exist modify broker, else add broker
    bool set_license_cfg(CFG_LICENSE& license);                 // if exist modify license, el se add license
    bool set_language_cfg(std::string value);                   // set/add language
    bool setConsoleStatus(bool status);                         // set/add console status
    bool setRootPath(std::string path);                         // set/add root path
};

}
#endif  // CONFIG_XML_H_
