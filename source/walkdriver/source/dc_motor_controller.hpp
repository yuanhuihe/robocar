
#include "executive_controller.hpp"
#include <fsgpio/fsgpio.h>

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
            memcpy(pin_gpio_map, devInfo.ctrl.pin_gpio_map, sizeof(pin_gpio_map));
            return 0;
        }
        
        virtual int setPin(int index, ElectricalLevel lvl)
        {
            if(avaliable())
            {
                int gpio_id = pin_gpio_map[index];
                return FSGPIO::GPIOWrite(gpio_id, lvl);
            }
                
            return -1;
        }

    private:
        int pin_gpio_map[MAX_PINS];
    };
    

} // namespace WalkDriver
