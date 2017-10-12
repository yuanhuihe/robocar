
#include "executivecontroller.hpp"


namespace WalkDriver
{
    class DCMotorController : public ExecutiveController
    {
    public:
        DCMotorController()
        {
        }
        ~DCMotorController()
        {
            delete controller;
        }
        
        virtual int setPin(int index, ElectricalLevel lvl)
        {

        }


    }
    

} // namespace WalkDriver
