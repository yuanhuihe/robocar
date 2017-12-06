#include "configxml.h"

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
    bool config::get_executive_bodies(std::vector<sExecutiveBody>& exe_bodies)
    {
        if (!xml_res)
        {
            print_error(__LINE__, "get load xml status error");
            return false;
        }
        pugi::xml_node _node = get_path_node("executives/body");

        int id = 0;
        while (_node)
        {
            sExecutiveBody body;
            memset(&body, 0, sizeof(body));

            body.id = id;

            body.type = atoi(_node.attribute("type").value());
            snprintf(body.name, sizeof(body.name) - 1, "%s", _node.attribute("name").value());

            pugi::xml_node _node_speed = _node.child("speed");
            if (_node_speed)
            {
                body.speed.range_min = atoi(_node_speed.child("range").attribute("mini").value());
                body.speed.range_max = atoi(_node_speed.child("range").attribute("max").value());
                body.speed.default_value = atoi(_node_speed.child_value("default"));

                if (body.speed.range_min<0)
                {
                    print_error(__LINE__, "speed range config error: min");
                    body.speed.range_min = 0;
                }
                if (body.speed.range_max <= body.speed.range_min)
                {
                    print_error(__LINE__, "speed range config error: max");
                    body.speed.range_max = body.speed.range_min + 1;
                }
                if (body.speed.default_value > body.speed.range_max)
                {
                    print_error(__LINE__, "speed range config error: default");
                    body.speed.default_value = body.speed.range_max;
                }
                if (body.speed.default_value < body.speed.range_min)
                {
                    print_error(__LINE__, "speed range config error: default");
                    body.speed.default_value = body.speed.range_min;
                }
            }

            pugi::xml_node act_node = _node.child("action");
            int act_cnt = 0;
            while (act_node && act_cnt<MAX_ACTION_CNT)
            {
                if (strcmp(act_node.name(), "action") != 0)
                {
                    break;
                }

                sAction& action = body.acts[act_cnt];
                action.id = act_cnt;
                action.parent_id = id;
                snprintf(action.name, sizeof(action.name) - 1, "%s", act_node.attribute("name").value());

                pugi::xml_node gpio_node = act_node.child("gpio");
                if (gpio_node)
                {
                    pugi::xml_node pin_node = gpio_node.child("pin");
                    int i = 0;
                    while (pin_node && i<MAX_GPIO_PINS)
                    {
                        int pin = atoi(pin_node.first_attribute().value());
                        int value = atoi(pin_node.last_attribute().value());
                        action.ctrls[i].pin = pin;
                        action.ctrls[i].value = value;
                        i++;
                        pin_node = pin_node.next_sibling();
                    }
                    action.ctrl_count = i;
                }

                act_cnt++;
                act_node = act_node.next_sibling();
            }
            body.act_count = act_cnt;

            exe_bodies.push_back(body);
            _node = _node.next_sibling();
        }

        return true;
    }
} // !namespace ConfigInfo
