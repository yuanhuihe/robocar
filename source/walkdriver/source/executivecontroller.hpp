
#include <walkdriver/walkdriver.h>
#include <walkdriver/ExecutiveDevice.h>


namespace WalkDriver
{
    // electrical level
    enum ElectricalLevel
    {
        NegativeLevel = -1,     // 负电平
        ZeroLevel,              // 零电平
        PositiveLevel,          // 正电平
    };

    class ExecutiveController
    {
    public:
        ExecutiveController()
        {

        }
        ~ExecutiveController()
        {

        }
        
        virtual int setPin(int index, ElectricalLevel lvl) = 0;
    }
    

} // namespace WalkDriver
