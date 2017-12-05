#ifndef XML_PARSER_HPP_
#define XML_PARSER_HPP_

#include "pugixml/pugixml.hpp"
#include "pugixml/pugiconfig.hpp"
#include "spdlog/spdlog.h"
#include "configdef.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#define XML_U8 pugi::encoding_utf8

typedef  pugi::xml_node        pxml_node;
typedef  pugi::xpath_node_set  pxpath_set;

namespace ConfigInfo
{
// string to any type(int, float...)
template <class Type>
Type stringToNum(const std::string& str)
{
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

// xml parser base class
class XML_Helper
{
protected:
    pugi::xml_parse_result xml_res;
    std::string xml_name;
    std::shared_ptr<spdlog::logger> l;
    pugi::xml_document xml_doc;

    bool _verbose;      // cout log
    bool _writeLog;     // write log
    bool _only_pt_err;  // only print error info

    xmlType_ m_Xtype;

    // enum xml_node return
    enum ENUM_RET
    {
        RET_SELF = 0,   // return self
        RET_PARENT = 1, // return parent
    };

    // enum xml_node find condition
    enum ENUM_PROPERTY
    {
        PROPERTY_NODE = 0,      // node value find index
        PROPERTY_ATTRIBUTE = 1, // node attribute find index
    };

protected:
    std::string getIntToString(int n)
    {
        std::stringstream newstr;
        newstr << n;
        return newstr.str();
    }

    int getStringToInt(std::string value)
    {
        int str_int = -1;
        if (value.empty()) return str_int;

        std::stringstream stream(value);
        stream >> str_int;
        return str_int;
    }

public:
    XML_Helper() : _verbose(true), _writeLog(false), _only_pt_err(true), m_Xtype(xmlType_::UNTYPE)
    {
        if (_writeLog) l = spdlog::get("xml");
    }
    ~XML_Helper() {}

    /*
     * @brief set current xml type
     * @param XML file type
     * @bak   if u used this as base class, u must set this class xml type when create child class constructor.
     * @备注  如果你使用该类作为基类，你必须在子类的构造函数中使用该函数指定当前类的xml类型
     */
    void set_curr_xml_type(xmlType_ type_)
    {
        m_Xtype = type_;
    }

    /*
     * @brief load XML file
     * @param XML file full path and file name
     * @return load status [true or false]
     */
    bool load_xml(std::string& xml_file_full_name)
    {
        xml_res = xml_doc.load_file(xml_file_full_name.c_str(), pugi::parse_default, XML_U8);
        if (!xml_res)  // judge xml load status
        {
            print_error(xml_res.offset, xml_res.description());
            return false;
        }
        print_info(__LINE__, "load success");
        return true;
    }

    /*
     * @brief Save XML to file
     * @param XML file path
     * @return save status
     */
    bool save_xml(std::string& xml_file_full_name)
    {
        bool result = false;
        if (!xml_res)
        {
            print_error(__LINE__, "get load_xml status error when save xml");
            return result;
        }

        result = xml_doc.save_file(xml_file_full_name.c_str(), "\t", pugi::format_default, XML_U8);
        if (!result)
        {
            print_error(__LINE__, "save xml failed.");
            return result;
        }
        print_info(__LINE__, "save xml success");
        return result;
    }

    /*
     * @brief create XML to file : only create xml head
     * @param XML file path
     * @return create status
     */
    bool create_xml(std::string& xml_file_full_name)
    {
        pugi::xml_document new_doc;
        bool result = false;

        // 1. judge xml isExist or not
        if (!load_xml(xml_file_full_name))
        {
            // create xml title
            pugi::xml_node base_node;
            switch (m_Xtype)
            {
            case xmlType_::APP_CONFIG:
                base_node = new_doc.append_child(HEAD_CFG);
                base_node.append_attribute("version").set_value(CFG_VERSION);
                base_node.append_attribute("name").set_value(NAME_VERSION);
            break;
            case xmlType_::DRIVER_ACTION:
            {
                // head : <xml><alice ...>
                base_node = new_doc.append_child(HEAD_EXE);
                base_node.append_attribute("version").set_value(EXE_VERSION);
                base_node.append_attribute("name").set_value(NAME_VERSION);
            }
            break;
            default:
                base_node = new_doc.append_child("xml");
            }

            result = new_doc.save_file(xml_file_full_name.c_str(), "\t", pugi::format_default, XML_U8);
            if (result)
            {
                // load new xml
                load_xml(xml_file_full_name);
                print_info(__LINE__, "create xml success");
            }
            else
            {
                print_error(__LINE__, "create xml failed.");
                return result;
            }
        }
        else
        {
            print_error(__LINE__, "create xml failed when check xml is exist.");
            return result;
        }

        return result;
    }

    /*
     * @brief create XML to file : create xml_data xml file
     * @param xml_data struct buffer
     * @return create status
     */
    bool create_xml(std::string xml_file_full_name, std::string xml_data)
    {
        try
        {
            std::ofstream out(xml_file_full_name.c_str());
            out << xml_data.c_str();
            out.close();
        }
        catch (...)
        {
            return false;
        }
        return true;
     }

    /*
     * @brief check file is xml
     * @param file full path & name
     * @return check status
     */
    bool check_xml(std::string& xml_file_name)
    {
        pugi::xml_document c_xml_doc;
        pugi::xml_parse_result c_xml_ret;
        c_xml_ret = c_xml_doc.load_file(xml_file_name.c_str(), pugi::parse_default, XML_U8);
        if (!c_xml_ret)
        {
            return false;
        }
        return true;
    }

    /*
     * @brief  get xml_path pugi::xml_node
     * @param  XML node path
     * @return pugi::xml_node
     */
    pugi::xml_node get_path_node(std::string xml_path)
    {
        if (!xml_res)
        {
            print_error(__LINE__, "get load_xml status error when get_path_node");
            return pugi::xml_node();
        }
        return xml_doc.select_node(xml_path.c_str()).node();
    }

    /*
     * @brief  get xml_path pugi::xml_node
     * @param  XML node path and search attribute
     * @return pugi::xml_node
     */
    pugi::xml_node get_path_node(std::string xml_path, std::string search_attribute)
    {
        if (!xml_res)
        {
            print_error(__LINE__, "get load_xml status error when get_path_node");
            return pugi::xml_node();
        }

        // Select nodes via compiled query
        pugi::xpath_variable_set vars;
        vars.add("value", pugi::xpath_type_string);		// set value type is string
        vars.set("value", search_attribute.c_str());    // value="rigid_name"

        pugi::xpath_node ret_xpath_node = xml_doc.select_node(xml_path.c_str(), &vars);
        return ret_xpath_node.node();
    }

    /*
     * @brief  get xml_path pugi::xml_node vector
     * @param  XML node path
     * @return pugi::xml_node vector
     */
    pugi::xpath_node_set get_path_nodes(std::string xml_path)
    {
        if (!xml_res)
        {
            print_error(__LINE__, "get load_xml status error when get_path_nodes");
            return pugi::xpath_node_set();
        }
        return xml_doc.select_nodes(xml_path.c_str());
    }

    /*
     * @brief  remove any node by xpath
     * @param  xpath string
     * @return remove status
     */
    bool remove_by_xpath(std::string xpath)
    {
        bool result = false;
        if (!xml_res)
        {
            print_error( __LINE__, "get load xml status error when remove by xpath");
            return result;
        }

        pugi::xml_node del_node = get_path_node(xpath);
        if (del_node)
        {
            pugi::xml_node del_parent = del_node.parent();
            if (del_parent)
            {
                // xml_node to remove(delete xml_node)
                result = del_parent.remove_child(del_node);
                if (result) print_info( __LINE__, "remove by xpath success");
            }
        }
        else { print_error( __LINE__, "get " + xpath + " data failed"); }
        return result;
    }

    /*
     * @brief  get node str value
     * @param  parent node & child node name
     * @return pugi::xml_node str_value
     */
    std::string getNodeChildValueStr(pugi::xml_node pNode, const std::string &node_name)
    {
        if (!pNode || node_name.empty()) return "";
        return pNode.child(node_name.c_str()).text().as_string("");
    }

    /*
     * @brief  get node int value
     * @param  parent node & child node name
     * @return pugi::xml_node int_value
     */
    int getNodeChildValueInt(pugi::xml_node pNode, const std::string &node_name)
    {
        if (!pNode || node_name.empty()) return -1;
        return pNode.child(node_name.c_str()).text().as_int(-1);
    }

    /*
     * @brief  get node float value
     * @param  parent node & child node name
     * @return pugi::xml_node float_value
     */
    float getNodeChildValueFloat(pugi::xml_node pNode, const std::string &node_name)
    {
        if (!pNode || node_name.empty()) return -1.0f;
        return pNode.child(node_name.c_str()).text().as_float(-1.0f);
    }

    /*
     * @brief  get node double value
     * @param  parent node & child node name
     * @return pugi::xml_node double_value
     */
    double getNodeChildValueDouble(pugi::xml_node pNode, const std::string &node_name)
    {
        if (!pNode || node_name.empty()) return -1.0;
        return pNode.child(node_name.c_str()).text().as_double(-1.0);
    }

    /*
     * @brief  get node bool value
     * @param  parent node & child node name
     * @return pugi::xml_node bool_value
     */
    bool getNodeChildValueBoolean(pugi::xml_node pNode, const std::string &node_name)
    {
        if (!pNode || node_name.empty()) return false;
        return pNode.child(node_name.c_str()).text().as_bool(false);
    }

    /*
     * @brief  get node attribute value
     * @param  xml_node self & attribute name
     * @return xml_node attribute str
     */
    std::string getNodeAttribute(pugi::xml_node mNode, const std::string &attribute_name)
    {
        if (!mNode || attribute_name.empty()) return "";
        return mNode.attribute(attribute_name.c_str()).as_string("");
    }

    /*
     * @brief get xpath is exist
     * @param xpath string ("/alice/rigid_body")
     */
    bool judge_xpath_isExist(std::string _xpath)
    {
        return (xml_res && (xml_doc.select_node(_xpath.c_str())).node()) ? true : false;
    }

    /*
     * @brief goto root node
     * get first node position
     */
    pugi::xml_node gotoRootNode()
    {
        // goto => /root_name, if not exist create it.
        pugi::xml_node base_node;
        switch (m_Xtype)
        {
        case xmlType_::APP_CONFIG:
        {
            // if not exists, create it.
            base_node = xml_doc.child(HEAD_CFG);
            if (!base_node)
            {
                base_node = xml_doc.append_child(HEAD_CFG);
                base_node.append_attribute("version").set_value(CFG_VERSION);
                base_node.append_attribute("name").set_value(NAME_VERSION);
            }
            return base_node;
        }
        break;
        case xmlType_::DRIVER_ACTION:
        {
            // if not exists, create it.
            base_node = xml_doc.child(HEAD_EXE);
            if (!base_node)
            {
                base_node = xml_doc.append_child(HEAD_CFG);
                base_node.append_attribute("version").set_value(EXE_VERSION);
                base_node.append_attribute("name").set_value(NAME_VERSION);
            }
            return base_node;
        }
        break;
        default:
            base_node = xml_doc.child("xml");
        }
        return base_node;
    }

    /*
     * @brief goto root child node
     * @param  root node -> child node name
     * get second node position
     */
    pugi::xml_node gotoRootChildNode(std::string child_name)
    {
        // goto => /root_name, if not exist create it.
        pugi::xml_node base_node = gotoRootNode();

        // goto => /root/... , if not exist create it.
        pugi::xml_node child_node = base_node.child(child_name.c_str());
        if (!child_node)
            child_node = base_node.append_child(child_name.c_str());

        return child_node;
    }

    /*
     * @brief get xml version
     * @return version string
     */
    std::string getXmlVersion()
    {
        pugi::xml_node base_node;
        switch (m_Xtype)
        {
        case xmlType_::APP_CONFIG:
        {
            base_node = xml_doc.child(HEAD_CFG);
        }
        break;
        case xmlType_::DRIVER_ACTION:
        {
            base_node = xml_doc.child(HEAD_EXE);
        }
        break;
        default:
            base_node = xml_doc.child("xml");
            break;
        }

        if (!base_node)
        {
            return "";
        }
        return base_node.attribute("version").as_string("");
    }

    /*
     * @brief get xml child version number
     * @return version string
     */
    std::string getXmlVersionChildNumber()
    {
        pugi::xml_node base_node;
        switch (m_Xtype)
        {
        case xmlType_::APP_CONFIG:
        {
            // head : <xml><alice ...>
            base_node = xml_doc.child(HEAD_CFG);
        }
        break;
        case xmlType_::DRIVER_ACTION:
        {
            // head : <xml><alice ...>
            base_node = xml_doc.child(HEAD_EXE);
        }break;
        default:
            base_node = xml_doc.child("xml");
        }

        if (!base_node)
        {
            return "";
        }
        return base_node.attribute("number").as_string("");
    }

    /*
     * @brief get xml version name
     * @return version string
     */
    std::string getXmlVersionName()
    {
        pugi::xml_node base_node;
        switch (m_Xtype)
        {
        case xmlType_::APP_CONFIG:
        {
            base_node = xml_doc.child(HEAD_CFG);
        }
        break;
        case xmlType_::DRIVER_ACTION:
        {
            base_node = xml_doc.child(HEAD_EXE);
        }
        break;
        default:
            base_node = xml_doc.child("xml");
        }
        if (!base_node)
        {
            return "";
        }
        return base_node.attribute("name").as_string("");
    }

protected:
    /*
     * @brief get xml type
     */
    std::string getXmlType()
    {
        switch(m_Xtype)
        {
        case xmlType_::UNTYPE:
        {
            return std::string("unknown");
        }
        case xmlType_::DRIVER_ACTION:
        {
            return std::string("DRIVER_ACTION");
        }
        case xmlType_::APP_CONFIG:
        {
            return std::string("App_Config");
        }
        default:
            return std::string("unknown");
        }
    }

    /*
     * @brief  print log and cout info
     */
    void print_info(int info_pos, std::string out_info)
    {
        if (_only_pt_err) return;
        if (_writeLog) l->debug("[INFO]  {}  {} XML file info : {}.", getXmlType(), info_pos, out_info);
        if (_verbose) std::cout << "[INFO]  " << getXmlType() << "  " << info_pos << " XML file info : " << out_info << "." << std::endl;
    }

    /*
     * @brief  print log and cout error info
     */
    void print_error(int err_pos, std::string err_info)
    {
        if (_writeLog) l->error("[ERROR]  {}  {} XML file error : {}.", getXmlType(), err_pos, err_info);
        if (_verbose) std::cout << "[ERROR]  " << getXmlType() << "  " << err_pos << " XML file error : " << err_info << "." << std::endl;
    }

    /* [protected]
     * @brief  remove any node by pugi::xml_node
     * @param  remove xml_node
     * @return remove status
     */
    bool remove_by_node(pugi::xml_node del_node)
    {
        if (!xml_res)
        {
            print_error( __LINE__, "get load xml status error when remove by node");
            return false;
        }

        if (del_node)
        {
            pugi::xml_node del_parent = del_node.parent();
            if (del_parent)
            {
                //remove del_node
                return del_parent.remove_child(del_node);
            }
        }
        return false;
    }

    /* [protected]
     * @brief accrss xpath_nodes find condition node and return find_node(RET_SELF)/find_node_parent(RET_PARENT)
     * @param xpath_nodes pugi::xpath_node_set (xml_node vector)
     *        condition   find node compare value
     *        find_index  find node_name or node_attribute_name
     *                      ..find node_name : if find self value find_index="", else find child value fild_index="child_name"
     *                      ..node_attribute_name : must fill in. (Tips: only find node self attribute.)
     *        ret         pugi::xml_node address( return find node self or parent)
     *        sty         pugi::xml_node compare property(compare node value or compare node attribute)
     * @return find node or parent pugi::xml_node
     */
    pugi::xml_node find_condition_node(pugi::xpath_node_set& xpath_nodes, std::string& condition, std::string find_index = "", ENUM_RET ret = RET_SELF, ENUM_PROPERTY sty = PROPERTY_NODE)
    {
        switch (sty) // get compare way
        {
        case ENUM_PROPERTY::PROPERTY_NODE: // find node name
        {
            if (find_index.empty()) // find node self value compare
            {
                for (auto &item : xpath_nodes)  // traversing nodes
                {
                    pugi::xml_node node = item.node();
                    if (node.text().get() == condition) // return node;
                    {
                        switch (ret)
                        {
                        case ENUM_RET::RET_SELF:
                        {
                            return node;
                        }break;
                        case ENUM_RET::RET_PARENT:
                        {
                            return node.parent();
                        }break;
                        default:
                            break;
                        }
                    }
                }
            }
            else // find node child(name=find_index) value compare
            {
                for (auto &item : xpath_nodes)  // traversing nodes
                {
                    pugi::xml_node node = item.node();
                    if (node.child(find_index.c_str()).text().get() == condition) // return node;
                    {
                        switch (ret)
                        {
                        case ENUM_RET::RET_SELF:
                        {
                            return node;
                        }break;
                        case ENUM_RET::RET_PARENT:
                        {
                            return node.parent();
                        }break;
                        default:
                            break;
                        }
                    }
                }
            }
        }break;
        case ENUM_PROPERTY::PROPERTY_ATTRIBUTE: // find node attribute
        {
            for (auto &item : xpath_nodes) // traversing nodes
            {
                pugi::xml_node node = item.node();
                if (node.attribute(find_index.c_str()).as_string() == condition) // return node;
                {
                    switch (ret)
                    {
                    case ENUM_RET::RET_SELF:
                    {
                        return node;
                    }break;
                    case ENUM_RET::RET_PARENT:
                    {
                        return node.parent();
                    }break;
                    default:
                        break;
                    }
                }
            }
        }break;
        default:
            break;
        }
        return pugi::xml_node();
    }
    // override
    /* [protected]
     * @brief accrss parent_node get children nodes to find condition node and return find_node(RET_SELF)/find_node_parent(PARENT)
     * @param find_parent_node (pugi::xml_node) find node parent node
     *        condition        find item value
     *        find_index       find node_name or node_attribute_name
     *                           ..find node_name : if find self value find_index="", else find child value fild_index="child_name"
     *                           ..node_attribute_name : must fill in. (Tips: only find node self attribute.)
     *        ret              pugi::xml_node address( return find node self or parent)
     *        sty              pugi::xml_node compare property(compare node value or compare node attribute)
     * @return find node or parent pugi::xml_node
     */
    pugi::xml_node find_condition_node(pugi::xml_node find_parent_node, std::string& condition, std::string find_index, ENUM_RET ret = RET_SELF, ENUM_PROPERTY sty = PROPERTY_NODE)
    {
        if (!find_parent_node)
            return pugi::xml_node();

        switch (sty) // get compare way
        {
        case ENUM_PROPERTY::PROPERTY_NODE: // find node name
        {
            if (find_index.empty()) // find node self value compare
            {
                for (auto &item : find_parent_node.children())  // traversing nodes
                {
                    if (item.text().get() == condition) // return node;
                    {
                        switch (ret)
                        {
                        case ENUM_RET::RET_SELF:
                        {
                            return item;
                        }break;
                        case ENUM_RET::RET_PARENT:
                        {
                            return item.parent();
                        }break;
                        default:
                            break;
                        }
                    }
                }
            }
            else // find node child(name=find_index) value compare
            {
                for (auto &item : find_parent_node.children())  // traversing nodes
                {
                    if (item.child(find_index.c_str()).text().get() == condition) // return node;
                    {
                        switch (ret)
                        {
                        case ENUM_RET::RET_SELF:
                        {
                            return item;
                        }break;
                        case ENUM_RET::RET_PARENT:
                        {
                            return item.parent();
                        }break;
                        default:
                            break;
                        }
                    }
                }
            }
        }break;
        case ENUM_PROPERTY::PROPERTY_ATTRIBUTE: // find node attribute
        {
            for (auto &item : find_parent_node.children()) // traversing nodes
            {
                if (item.attribute(find_index.c_str()).as_string() == condition) // return node;
                {
                    switch (ret)
                    {
                    case ENUM_RET::RET_SELF:
                    {
                        return item;
                    }break;
                    case ENUM_RET::RET_PARENT:
                    {
                        return item.parent();
                    }break;
                    default:
                        break;
                    }
                }
            }
        }break;
        default:
            break;
        }
        return pugi::xml_node();
    }

};
} // !ConfigInfo

#endif // XML_PARSER_HPP_
