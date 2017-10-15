
#include <walkdriver/walkdriver.h>
#include <walkdriver/executive_device.h>


namespace WalkDriver
{
    // electrical level
    enum ElectricalLevel
    {
        NegativeLevel = -1,     // ����ƽ
        ZeroLevel,              // ���ƽ
        PositiveLevel,          // ����ƽ
    };

    class ExecutiveController
    {
    public:
        ExecutiveController()
        {

        }
        virtual ~ExecutiveController()
        {

        }

        virtual void reset() = 0;

        virtual int setGPIOMap(DEV_INFO devInfo) = 0;
        
        virtual int setPin(int index, ElectricalLevel lvl) = 0;

        virtual bool avaliable() = 0;
    };
    

} // namespace WalkDriver
