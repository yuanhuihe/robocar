
/* gpiorw.cpp
*
* Raspberry Pi GPIO r/w interface.
* by Yuanhui HE, 2017.10.12.
*
*/

#include "gpiorw/gpiorw.h"
#include "gpio_base.hpp"
#include "fsgpio.hpp"
#include "wiringpi_gpio.hpp"


namespace GPIORW
{
    GPIOFunctionType maptype = GFT_WiringPi;
    gpio_base* gpio = new WiringPiGPIO();


    GPIORW_API void GPIOLibInit(GPIOFunctionType type)
    {
        if (maptype != type)
        {
            delete gpio;
            switch (type)
            {
            case GPIORW::GFT_WiringPi:
                maptype = type;
                gpio = new WiringPiGPIO();
                break;
            case GPIORW::GFT_FileSystem:
                maptype = type;
                gpio = new FileSystemGPIO();
                break;
            default:
                maptype = GFT_WiringPi;
                gpio = new WiringPiGPIO();
                break;
            }
        }

        gpio->Init();
    }

    GPIORW_API void GPIOLibRelease()
    {
        gpio->Release();
    }

    GPIORW_API int GPIORead(int pin)
    {
        return gpio->GPIORead(pin);
    }

    GPIORW_API int GPIOWrite(int pin, int value)
    {
        return gpio->GPIOWrite(pin, value);
    }


} // namespace GPIORW
