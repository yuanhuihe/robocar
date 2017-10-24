
#include "executive_controller.hpp"
#include <gpiorw/gpiorw.h>

namespace WalkDriver
{
    class DCMotorController : public ExecutiveController
    {
    public:
        DCMotorController()
        {
        }
        virtual ~DCMotorController()
        {
        }

        virtual void reset()
        {

        }

        virtual bool avaliable()
        {
            // TBD: should read gpio to make sure wether the device is alive.
            return true;
        }

        virtual int setGPIOMap(DEV_INFO devInfo)
        {
            memset(pin_map, -1, sizeof(pin_map));
            for (int i = 0; i < devInfo.ctrl.pin_count; i++)
            {
                pin_map[i] = devInfo.ctrl.pin_map[i];
            }

            return 0;
        }
        
        virtual int setPin(int index, ElectricalLevel lvl)
        {
            if(avaliable())
            {
                int pin_id = pin_map[index];
                return GPIORW::GPIOWrite(pin_id, lvl);
            }
                
            return -1;
        }

    private:
        int pin_map[MAX_PINS];
    };
    

} // namespace WalkDriver
