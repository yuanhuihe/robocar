#include "configxml.h"

// #include <stdio.h>
// #include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace ConfigInfo
{

config::config(xmlType_ type)
{
    set_curr_xml_type(type);
}

config::~config()
{
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
 * @brief set/add language
 * @return set/add status
 */
bool config::set_language_cfg(char* value)
{
    bool result = false;
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error when set_language_cfg");
        return result;
    }

    pugi::xml_node language_node = gotoRootChildNode("language");
    language_node.text().set(value);
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
bool config::get_actions(std::vector<sActionConfig>& actions)
{
    if (!xml_res)
    {
        print_error(__LINE__, "get load xml status error");
        return false;
    }
    pugi::xml_node _node = get_path_node("executive/actions/action");
    while (_node)
    {
        sActionConfig action;
        memset(&action, 0, sizeof(action));
        
        action.type = atoi(_node.child_value("type"));
        snprintf(action.name, sizeof(action.name) - 1, "%s", _node.child_value("name"));

        pugi::xml_node ctrl = _node.child("control");
        pugi::xml_node gpio = ctrl.child("gpio");
        int i = 0;
        while (gpio)
        {
            int pin = atoi(gpio.first_attribute().value());
            int value = atoi(gpio.last_attribute().value());
            if( pin < MAX_GPIO_PINS)
            {
                action.ctrls[i].pin = pin;
                action.ctrls[i].value = value;
                i++;
            }

            gpio = gpio.next_sibling();
        }
        action.ctrl_count = i;


        pugi::xml_node _node_speed = _node.child("speed");
        if(_node_speed)
        {
            action.speed.has_speed = true;
            action.speed.range_min = atoi(_node_speed.child("range").attribute("mini").value());
            action.speed.range_max = atoi(_node_speed.child("range").attribute("max").value());
            action.speed.default_value = atoi(_node_speed.child_value("default"));

            if(action.speed.range_min<0)
            {
                print_error(__LINE__, "speed range config error: min");
                action.speed.range_min = 0;
            } 
            if(action.speed.range_max <= action.speed.range_min )
            {
                print_error(__LINE__, "speed range config error: max");
                action.speed.range_max = action.speed.range_min + 1;
            } 
            if(action.speed.default_value > action.speed.range_max)
            {
                print_error(__LINE__, "speed range config error: default");
                action.speed.default_value = action.speed.range_max;
            } 
            if(action.speed.default_value < action.speed.range_min)
            {
                print_error(__LINE__, "speed range config error: default");
                action.speed.default_value = action.speed.range_min;
            } 
        }
        else
        {
            action.speed.has_speed = false;
        }

        actions.push_back(action);

        _node = _node.next_sibling();
    }

    return true;
}
} // !namespace ConfigInfo
