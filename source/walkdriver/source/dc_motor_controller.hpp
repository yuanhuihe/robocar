
#include "executive_controller.hpp"


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
        }
        
        virtual int setPin(int index, ElectricalLevel lvl)
        {

        }
    }
    

} // namespace WalkDriver
