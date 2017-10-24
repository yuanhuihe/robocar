
/* wiringpi_gpio.hpp
*
* Raspberry Pi GPIO r/w using WiringPi.
* by Yuanhui HE, 2017.10.12.
*
*/
#pragma once

#ifndef WIN32


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
            //-----------Pin---wPiIO---Name------------------------------------------
            PinToWiringPi[0] = -1;  // Pin number is start from 1, 0 is not available
            PinToWiringPi[1] = -1;  // 3.3v DC Power
            PinToWiringPi[2] = -1;  // 5v DC Power
            PinToWiringPi[3] = 8;   // GPIO 02(SDA1, I2C)
            PinToWiringPi[4] = -1;  // 5v DC Power
            PinToWiringPi[5] = 9;   // GPIO 03(SCL1, I2C)
            PinToWiringPi[6] = -1;  // Ground
            PinToWiringPi[7] = 7;   // GPIO 04(GPIO_GCLK)
            PinToWiringPi[8] = 15;  // GPIO 14(TXD0)
            PinToWiringPi[9] = -1;  // Ground
            PinToWiringPi[10] = 16; // GPIO 15(RXD0)
            PinToWiringPi[11] = 0;  // GPIO 17(GPIO_GEN0)
            PinToWiringPi[12] = 1;  // GPIO 18(GPIO_GEN1)
            PinToWiringPi[13] = 2;  // GPIO 27(GPIO_GEN2)
            PinToWiringPi[14] = -1; // Ground
            PinToWiringPi[15] = 3;  // GPIO 22(GPIO_GEN3)
            PinToWiringPi[16] = 4;  // GPIO 23(GPIO_GEN4)
            PinToWiringPi[17] = -1; // 3.3v DC Power
            PinToWiringPi[18] = 5;  // GPIO 24(GPIO_GEN5)
            PinToWiringPi[19] = 12; // GPIO 10(SPI_MOSI)
            PinToWiringPi[20] = -1; // Ground
            PinToWiringPi[21] = 13; // GPIO 09(SPI_MOSO)
            PinToWiringPi[22] = 6;  // GPIO 25(GPIO_GEN6)
            PinToWiringPi[23] = 14; // GPIO 11(SPI_CLK)
            PinToWiringPi[24] = 10; // GPIO 08(SPI_CE0_N)
            PinToWiringPi[25] = -1; // Ground
            PinToWiringPi[26] = 11; // GPIO 07(SPI_CE1_N)
            PinToWiringPi[27] = 30; // ID_SD(I2C ID EEPRO)
            PinToWiringPi[28] = 31; // ID_SC(I2C ID EEPRO)
            PinToWiringPi[29] = 21; // GPIO 05
            PinToWiringPi[30] = -1; // Ground
            PinToWiringPi[31] = 22; // GPIO 06
            PinToWiringPi[32] = 26; // GPIO 12
            PinToWiringPi[33] = 23; // GPIO 13
            PinToWiringPi[34] = -1; // Ground
            PinToWiringPi[35] = 24; // GPIO 19
            PinToWiringPi[36] = 27; // GPIO 16
            PinToWiringPi[37] = 25; // GPIO 26
            PinToWiringPi[38] = 28; // GPIO 20
            PinToWiringPi[39] = -1; // Ground
            PinToWiringPi[40] = 29; // GPIO 21

            if (wiringPiSetup() == -1)
            {
                fprintf(stderr, "wiringPiSetup failed\n");
                return 1;
            }
			
			fprintf(stderr, "wiringPiSetup successfully\n");
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
            pinMode(wport, INPUT);
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
            digitalWrite(wport, value);
            return 0;
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

#endif // !WIN32