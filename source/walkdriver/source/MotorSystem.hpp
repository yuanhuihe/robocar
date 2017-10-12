
#pragma once

#include <walkdriver/walkdriver.h>
#include "configxml.h"


namespace WalkDriver
{
    class MotorSystem : public WalkSystem
    {
    public:
        MotorSystem()
        {

        }
        virtual ~MotorSystem()
        {

        }

        ExecutiveDevice* enumExecutiveBody()
        {
            //// 2. ¼ÓÔØÅäÖÃÎÄ¼þ
            //XmlBus::Get()->Load();
            ////MotorSystem.xml
            xmlbus::config cfg;
            std::string file = "MotorSystem.xml";
            cfg.load_xml(file);


            return nullptr;
        }

    private:

    };

} // namespace WalkDriver
