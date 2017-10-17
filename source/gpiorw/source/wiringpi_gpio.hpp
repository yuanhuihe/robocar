
/* wiringpi_gpio.hpp
*
* Raspberry Pi GPIO r/w using WiringPi.
* by Yuanhui HE, 2017.10.12.
*
*/
#pragma once

#include "_inl.hpp"
#include "gpiorw/gpiorw.h"
#include "gpio_base.hpp"
#include <wiringPi.h>

namespace GPIORW
{
    class WiringPiGPIO : public gpio_base
    {
    public:
        WiringPiGPIO()
        {

        }
        virtual ~WiringPiGPIO()
        {

        }

        virtual int Init()
        {
            memset(PinToWiringPi, 0, sizeof(PinToWiringPi));
            PinToWiringPi[0] = -1;
            PinToWiringPi[1] = -1;
            PinToWiringPi[2] = 8;
            PinToWiringPi[3] = -1;
            PinToWiringPi[4] = 9;
            PinToWiringPi[5] = -1;
            PinToWiringPi[6] = 7;
            PinToWiringPi[7] = 15;
            PinToWiringPi[8] = -1;
            PinToWiringPi[9] = 16;
            PinToWiringPi[10] = 0;
            PinToWiringPi[11] = 1;
            PinToWiringPi[12] = 2;
            PinToWiringPi[13] = -1;
            PinToWiringPi[14] = 3;
            PinToWiringPi[15] = 4;
            PinToWiringPi[16] = -1;
            PinToWiringPi[17] = 5;
            PinToWiringPi[18] = 12;
            PinToWiringPi[19] = -1;
            PinToWiringPi[20] = 13;
            PinToWiringPi[21] = 6;
            PinToWiringPi[22] = 14;
            PinToWiringPi[23] = 10;
            PinToWiringPi[24] = -1;
            PinToWiringPi[25] = 11;
            PinToWiringPi[26] = 30;
            PinToWiringPi[27] = 31;
            PinToWiringPi[28] = 21;
            PinToWiringPi[29] = -1;
            PinToWiringPi[30] = 22;
            PinToWiringPi[31] = 26;
            PinToWiringPi[32] = 23;
            PinToWiringPi[33] = -1;
            PinToWiringPi[34] = 24;
            PinToWiringPi[35] = 27;
            PinToWiringPi[36] = 25;
            PinToWiringPi[37] = 28;
            PinToWiringPi[38] = -1;
            PinToWiringPi[39] = 29;

            if (wiringPiSetup() == -1)
                return 1;
            else
                return 0;
        }

        virtual void Release()
        {
            memset(PinToWiringPi, 0, sizeof(PinToWiringPi));
        }

        virtual int GPIORead(int pin)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }

            int wport = PinToWiringPi[pin];
            pinMode(wport, INTPUT);
            return digitalRead(wport);
        }

        virtual int GPIOWrite(int pin, int value)
        {
            if (0 != checkPin(pin))
            {
                return -1;
            }
            int wport = PinToWiringPi[pin];
            pinMode(wport, OUTPUT);
            return digitalWrite(wport, value);
        }

    private:
        char PinToWiringPi[PIN_MAX_COUNT];
        int checkPin(int pin)
        {
            // check pin range
            if (pin < 0 || pin >= PIN_MAX_COUNT)
            {
                fprintf(stderr, "Pin '%d' error\n", pin);
                return -1;
            }
            // check pin map to wiring pi is avalible
            if (PinToWiringPi[pin]==-1)
            {
                fprintf(stderr, "Pin '%d' WiringPi map failed\n", pin);
                return -1;
            }

            return 0;
        }


    };

} // namespace GPIORW
