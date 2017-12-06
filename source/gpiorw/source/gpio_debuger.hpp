
/* win32debuggpio.hpp
*
* Only for debug call flow on Windows for GPIO r/w.
* by Yuanhui HE, 2017.10.18.
*
*/
#pragma once

#include "_inl.hpp"
#include "gpio_base.hpp"

namespace GPIORW
{
    class GpioCrossplatformDebuger : public gpio_base
    {
    public:
        GpioCrossplatformDebuger()
        {
        }
        virtual ~GpioCrossplatformDebuger()
        {
        }

        virtual int Init()
        {
            fprintf(stderr, "<GpioDebuger>Init()\n");
            return 0;
        }

        virtual void Release()
        {
            fprintf(stderr, "<GpioDebuger>Release()\n");
        }

        virtual int GPIORead(int pin)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }

            fprintf(stderr, "<GpioDebuger>GPIORead(pin:%d)\n", pin);
            return 0;
        }

        virtual int GPIOWrite(int pin, int value)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }

            fprintf(stderr, "<GpioDebuger>GPIOWrite(pin:%d, value:%d)\n", pin, value);
            return 0;
        }

    private:

        int checkPin(int pin)
        {
            // check pin range
            if (pin < 0 || pin >= PIN_MAX_COUNT)
            {
                fprintf(stderr, "<GpioDebuger>checkPin(pin:%d) error\n", pin);
                return -1;
            }

            return 0;
        }
    };

} // namespace GPIORW
