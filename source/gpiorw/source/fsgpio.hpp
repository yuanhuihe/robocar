
/* fsgpio.hpp
*
* Raspberry Pi GPIO r/w using sysfs interface.
* Guillermo A. Amaral B. <g@maral.me>, first version.
* Modified by Yuanhui HE, 2017.10.12.
*
*/
#pragma once

#include "_inl.hpp"
#include "gpiorw/gpiorw.h"
#include "gpio_base.hpp"

namespace GPIORW
{
    class FileSystemGPIO : public gpio_base
    {
#define VALUE_MAX 30
#define BUFFER_MAX 3
    public:
        FileSystemGPIO()
        {

        }
        virtual ~FileSystemGPIO()
        {

        }

        virtual int Init()
        {
            memset(isPinExported, 0, sizeof(isPinExported));
            memset(isPinExportedAsInput, 0, sizeof(isPinExportedAsInput));
        }

        virtual void Release()
        {
            for (int i = 0; i < PIN_MAX_COUNT; i++)
            {
                if (isPinExported[i])
                {
                    GPIOUnexport(i);
                    isPinExported[i] = 0;
                    isPinExportedAsInput[i] = 0;
                }
            }
            memset(isPinExported, 0, sizeof(isPinExported));
            memset(isPinExportedAsInput, 0, sizeof(isPinExportedAsInput));
        }

        virtual int GPIORead(int pin)
        {
            char path[VALUE_MAX];
            char value_str[3];
            int fd;

            if (0 != checkPin(pin, OUT))
            {
                return -1;
            }

            snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
            fd = open(path, O_RDONLY);
            if (-1 == fd) {
                fprintf(stderr, "Failed to open gpio value for reading!\n");
                return(-1);
            }

            if (-1 == read(fd, value_str, 3)) {
                fprintf(stderr, "Failed to read value!\n");
                return(-1);
            }

            close(fd);

            return(atoi(value_str));
        }

        virtual int GPIOWrite(int pin, int value)
        {
            static const char s_values_str[] = "01";

            char path[VALUE_MAX];
            int fd;

            if (0 != checkPin(pin, IN))
            {
                return -1;
            }

            snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
            fd = open(path, O_WRONLY);
            if (-1 == fd) {
                fprintf(stderr, "Failed to open gpio value for writing!\n");
                return(-1);
            }

            if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
                fprintf(stderr, "Failed to write value!\n");
                return(-1);
            }

            close(fd);
            return(0);
        }

    private:

        char isPinExported[PIN_MAX_COUNT];          // 0 means not exported
        char isPinExportedAsInput[PIN_MAX_COUNT];   // 0 means not set, 1 means set as input, 2 means set as ouptput

        int GPIOExport(int pin)
        {
            char buffer[BUFFER_MAX];
            ssize_t bytes_written;
            int fd;

            fd = open("/sys/class/gpio/export", O_WRONLY);
            if (-1 == fd) {
                fprintf(stderr, "Failed to open export for writing!\n");
                return(-1);
            }

            bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
            write(fd, buffer, bytes_written);
            close(fd);
            return(0);
        }

        int GPIOUnexport(int pin)
        {
            char buffer[BUFFER_MAX];
            ssize_t bytes_written;
            int fd;

            fd = open("/sys/class/gpio/unexport", O_WRONLY);
            if (-1 == fd) {
                fprintf(stderr, "Failed to open unexport for writing!\n");
                return(-1);
            }

            bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
            write(fd, buffer, bytes_written);
            close(fd);
            return(0);
        }

        int GPIODirection(int pin, int dir)
        {
            static const char s_directions_str[] = "in\0out";

#define DIRECTION_MAX 35
            char path[DIRECTION_MAX];
            int fd;

            snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
            fd = open(path, O_WRONLY);
            if (-1 == fd) {
                fprintf(stderr, "Failed to open gpio direction for writing!\n");
                return(-1);
            }

            if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
                fprintf(stderr, "Failed to set direction!\n");
                return(-1);
            }

            close(fd);
            return(0);
        }

        int checkPin(int pin, int direction)
        {
            // check pin range
            if (pin < 0 || pin >= PIN_MAX_COUNT)
            {
                fprintf(stderr, "Pin '%d' error\n", pin);
                return -1;
            }

            // check export stat
            if (!isPinExported[pin])
            {
                if (0 == GPIOExport(pin))
                {
                    isPinExported[pin] = 1;
                    fprintf(stderr, "Pin '%d' set as 'Exported'\n", pin);
                }
                else
                {
                    fprintf(stderr, "Pin '%d' set export failed\n", pin);
                    return -1;
                }
            }

            // check direction
            char dir = (IN == direction ? 1 : 2);
            if (isPinExportedAsInput[pin] != dir)
            {
                if (0 == GPIODirection(pin, direction))
                {
                    isPinExportedAsInput[pin] = dir;
                    fprintf(stderr, "Pin '%d' set as '%s' successfully\n", pin, (IN == direction ? "IN" : "OUT"));
                }
                else
                {
                    fprintf(stderr, "Pin '%d' set as '%s' failed\n", pin, (IN == direction ? "IN" : "OUT"));
                    return -1;
                }
            }

            return 0;
        }


    };

} // namespace GPIORW
