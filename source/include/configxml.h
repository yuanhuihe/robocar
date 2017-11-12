#ifndef CONFIG_XML_H_
#define CONFIG_XML_H_

#include <string>

#include "xml_parser.hpp"
#include "configdef.hpp"

namespace ConfigInfo
{

class config : public XML_Helper
{
public:
    config(xmlType_ type);
    ~config();

    // GET =========================================================================================
    std::string get_language_cfg();                             // get language
    bool getConsoleStatus();                                    // get console status
    std::string getRootPath();                                  // get root path

    bool get_actions(std::vector<sActionConfig>& actions);

    // SET =========================================================================================
    bool set_language_cfg(std::string value);                   // set/add language
    bool setConsoleStatus(bool status);                         // set/add console status
    bool setRootPath(std::string path);                         // set/add root path
};

} // !namespace ConfigInfo
#endif  // CONFIG_XML_H_
