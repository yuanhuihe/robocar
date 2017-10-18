
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
    class Win32DebugGpio : public gpio_base
    {
    public:
        Win32DebugGpio()
        {
            fprintf(stderr, "Win32DebugGpio constructor\n");
        }
        virtual ~Win32DebugGpio()
        {
            fprintf(stderr, "Win32DebugGpio destructor\n");
        }

        virtual int Init()
        {
            fprintf(stderr, "Win32DebugGpio Init()\n");
            return 0;
        }

        virtual void Release()
        {
            fprintf(stderr, "Win32DebugGpio Release()\n");
        }

        virtual int GPIORead(int pin)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }

            fprintf(stderr, "Win32DebugGpio GPIORead(pin:%d)\n", pin);
            return 0;
        }

        virtual int GPIOWrite(int pin, int value)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }

            fprintf(stderr, "Win32DebugGpio GPIOWrite(pin:%d, value:%d)\n", pin, value);
            return 0;
        }

    private:

        int checkPin(int pin)
        {
            // check pin range
            if (pin < 0 || pin >= PIN_MAX_COUNT)
            {
                fprintf(stderr, "Win32DebugGpio checkPin(pin:%d) error\n", pin);
                return -1;
            }

            return 0;
        }


    };

} // namespace GPIORW
