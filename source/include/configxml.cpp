#include "configxml.h"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace xmlbus
{

config::config(xmlType_ type)
{
    set_curr_xml_type(type);
}

config::~config()
{
}

/*
 * @brief   get broker
 * @return  broker struct data
 * @explain access return CFG_BROKER->ret_flag item to judge broker struct data valid.
 */
CFG_BROKER config::get_broker_cfg()
{
    CFG_BROKER ret_broker;
    ret_broker.ret_flag = false;

    pugi::xml_node broker_node = get_path_node("config/broker");
    if (broker_node)
    {
        ret_broker.id = broker_node.child_value("id");
        ret_broker.ip = broker_node.child_value("ip");
        ret_broker.port_proxy_s = broker_node.child("port").child_value("proxy_s");
        ret_broker.port_pub_s = broker_node.child("port").child_value("pub_s");
        ret_broker.port_proxy_c = broker_node.child("port").child_value("proxy_c");
        ret_broker.port_pub_c = broker_node.child("port").child_value("pub_c");
        ret_broker.ret_flag = true;
        print_info(__LINE__, "get config/broker data success.");
    }
    else
    {
        print_error(__LINE__, "Cannot find config/broker when get_broker");
    }

    return ret_broker;
}

/*
 * @brief get license
 * @return license struct data
 * @explain access return CFG_LICENSE->ret_flag item to judge broker struct data valid.
 */
CFG_LICENSE config::get_license_cfg()
{
    CFG_LICENSE ret_lic;
    ret_lic.ret_flag = false;

    pugi::xml_node license_node = get_path_node("config/license");
    if (license_node)
    {
        ret_lic.ip = license_node.child_value("server");
        ret_lic.port = license_node.child_value("port");
        ret_lic.end_time = license_node.child("time").child_value("end_time");
        ret_lic.login_systime = license_node.child("time").child_value("login_systime");
        ret_lic.sn = license_node.child_value("license_sn");
        ret_lic.client_config = license_node.child_value("ClientConfig");
        ret_lic.ret_flag = true;
        print_info(__LINE__, "get config/license data success");
    }
    else
    {
        print_error(__LINE__, "get config/license data failed");
    }
    return ret_lic;
}

/*
 * @brief get language
 * @return language type string
 */
std::string config::get_language_cfg()
{
    std::string ret_str = "";
    pugi::xml_node language_node = get_path_node("config/language");
    if (language_node)
    {
        ret_str = language_node.text().get();
        print_info(__LINE__, "get config/language data success");
    }
    else
    {
        print_error(__LINE__, "get config/language data failed");
    }
    return ret_str;
}

/*
 * @brief  if exist modify broker, else add broker
 * @return set/add status
 */
bool config::set_broker_cfg(CFG_BROKER &broker)
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when set_broker_cfg");
        return result;
    }

    // verify broker data valid.
    if (broker.ip.empty() || broker.port_proxy_s.empty() || broker.port_pub_s.empty() || broker.port_proxy_c.empty() || broker.port_pub_c.empty())
    {
        print_error(__LINE__, "Set broker struct data maybe invalid");
        return result;
    }

    // goto => if not exist create it.
    pugi::xml_node _node = gotoRootNode();

    pugi::xml_node broker_node = _node.child("broker");
    if (broker_node) // broker_node exist
    {
        remove_by_node(broker_node.child("id"));
        remove_by_node(broker_node.child("ip"));
        remove_by_node(broker_node.child("port"));
    }

    // TODO: add broker
    broker_node = gotoRootChildNode("broker");
    broker_node.append_child("id").text().set(broker.id.c_str());
    broker_node.append_child("ip").text().set(broker.ip.c_str());
    pugi::xml_node broker_port = broker_node.append_child("port");
    broker_port.append_child("proxy_s").text().set(broker.port_proxy_s.c_str());
    broker_port.append_child("pub_s").text().set(broker.port_pub_s.c_str());
    broker_port.append_child("proxy_c").text().set(broker.port_proxy_c.c_str());
    broker_port.append_child("pub_c").text().set(broker.port_pub_c.c_str());
    result = true;
    print_info(__LINE__, "add broker node success");
    return result;
}

/*
 * @brief  if exist modify license, el se add license
 * @return set/add status
 */
bool config::set_license_cfg(CFG_LICENSE &license)
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when set_license_cfg");
        return result;
    }

    // verify license data valid.
    if (license.ip.empty() || license.port.empty() || license.end_time.empty() ||
        license.login_systime.empty() || license.sn.empty())
    {
        print_error(__LINE__, "Set license struct data maybe invalid");
        return result;
    }

    pugi::xml_node _node = gotoRootNode();
    pugi::xml_node license_node = _node.child("license");
    if (license_node)
    {
        // TODO: license_node exist, modify license
        license_node.child("server").text().set(license.ip.c_str());
        license_node.child("port").text().set(license.port.c_str());
        license_node.child("time").child("end_time").text().set(license.end_time.c_str());
        license_node.child("time").child("login_systime").text().set(license.login_systime.c_str());
        license_node.child("license_sn").text().set(license.sn.c_str());
        license_node.child("ClientConfig").text().set(license.client_config.c_str());
        result = true;
        print_info(__LINE__, "modify sdk node success");
    }
    else
    {
        // add license
        license_node = _node.append_child("license");
        license_node.append_child("server").text().set(license.ip.c_str());
        license_node.append_child("port").text().set(license.port.c_str());
        pugi::xml_node time_node = license_node.append_child("time");
        time_node.append_child("end_time").text().set(license.end_time.c_str());
        time_node.append_child("login_systime").text().set(license.login_systime.c_str());
        license_node.append_child("license_sn").text().set(license.sn.c_str());
        license_node.append_child("ClientConfig").text().set(license.client_config.c_str());
        result = true;
        print_info(__LINE__, "add sdk node success");
    }
    return result;
}

/*
 * @brief set/add language
 * @return set/add status
 */
bool config::set_language_cfg(std::string value)
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when set_language_cfg");
        return result;
    }

    pugi::xml_node language_node = gotoRootChildNode("language");
    language_node.text().set(value.c_str());
    result = true;

    return result;
}

/*
 * @brief get console status
 * @return console status
 */
bool config::getConsoleStatus()
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when getConsoleStatus");
        return result;
    }
    pugi::xml_node console_node = get_path_node("config/console");
    if (console_node)
    {
        result = console_node.text().as_bool();
        print_info(__LINE__, "get config/console data success");
    }
    else
    {
        print_error(__LINE__, "get config/console data failed");
    }
    return result;
}

/*
 * @brief set/add console status
 * @return set/add status
 */
bool config::setConsoleStatus(bool status)
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when setConsoleStatus");
        return result;
    }

    pugi::xml_node console_node = gotoRootChildNode("console");
    console_node.text().set(status);
    result = true;

    return result;
}

/*
 * @brief get root path
 * @return get path
 */
std::string config::getRootPath()
{
    std::string result = "";
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when getRootPath");
        return result;
    }
    pugi::xml_node path_node = get_path_node("config/rootpath");
    if (path_node)
    {
        result = path_node.text().as_string();
        print_info(__LINE__, "get config/rootpath data success");
    }
    else
    {
        print_error(__LINE__, "get config/rootpath data failed");
    }
    return result;
}

/*
 * @brief set/add root path
 * @return set/add status
 */
bool config::setRootPath(std::string path)
{
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when setRootPath");
        return false;
    }

    pugi::xml_node path_node = gotoRootChildNode("rootpath");
    path_node.text().set(path.c_str());
    return true;
}


/*
 * @brief set/add root path
 * @return set/add status
 */
bool config::get_walk_device()
{
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when get_walk_device");
        return false;
    }
    pugi::xml_node _node = get_path_node("walkdevice/executives/dev");
    while (_node)
    {
        DEV dev;
        dev.id = atoi(_node.child_value("id"));
        snprintf(dev.name, sizeof(dev.name) - 1, "%s", _node.child_value("name"));
        dev.dev_type = atoi(_node.child_value("dev_type"));

        pugi::xml_node ctrl = _node.child("controller");
        pugi::xml_node pins = ctrl.child("pins");
        pugi::xml_node pin = pins.child("pin");
        int i = 0;
        while (pin && i < MAX_PINS)
        {
            int index = atoi(pin.child_value("index"));
            dev.ctrl.pin_gpio_map[i][index] = atoi(pin.child_value("gpio"));
            i++;

            pin = pin.next_sibling();
        }
        dev.ctrl.pin_count = i;

        _node = _node.next_sibling();
    }

    return true;
}
}
