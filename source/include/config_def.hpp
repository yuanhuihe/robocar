#ifndef CONFIG_DEF_HPP_
#define CONFIG_DEF_HPP_

#include <string>
#include <vector>

namespace xmlbus
{
    // config broker
    struct CFG_BROKER
    {
        std::string id;             // server broker id
        std::string ip;             // server broker ip
        std::string port_proxy_s;   // server broker port proxy
        std::string port_pub_s;     // server broker port pub
        std::string port_proxy_c;   // client broker port proxy
        std::string port_pub_c;     // client broker port pub
        bool ret_flag;              // current struct data validity, omissible
    };


    // config license
    struct CFG_LICENSE
    {
        std::string ip;
        std::string port;
        std::string end_time;
        std::string login_systime;
        std::string client_config;
        std::string sn;
        bool ret_flag;    // current struct data validity, omissible
    };
    
    /* <module name = "main" loaded = "true"> */
    // module base info
    struct MODULE_INFO
    {
        std::string name;
        bool loaded;
    };


    //<log>
    //	<filename>main</filename>
    //	<level>0</level>
    //</log>
    // module log info
    struct LOG
    {
        std::string path;
        std::string name;
        int level_;
    };

    // config module main
    struct CFG_MD_MAIN
    {
        MODULE_INFO info;
        LOG log;
        void init(std::string name)
        {
            info.name = name;
            info.loaded = true;
            log.path = "";
            log.name = name;
            log.level_ = 0;
        }
    };
    
    // app
    typedef struct APP_ITEM
    {
        std::string _name;
        std::string _xml_path;
        std::string _cont_path;
    }app_item;

} // namespace xmlbus
#endif // CONFIG_DEF_HPP_
