
/* gpio_base.hpp
*
* gpio interface base class.
* by Yuanhui HE, 2017.10.12.
*
*/
#pragma once

namespace GPIORW
{
    class gpio_base
    {
    public:
        gpio_base() {}
        virtual ~gpio_base() {}

        virtual int Init() = 0;
        virtual void Release() = 0;
        virtual int GPIORead(int pin) = 0;
        virtual int GPIOWrite(int pin, int value) = 0;
    };

} // namespace GPIORW
