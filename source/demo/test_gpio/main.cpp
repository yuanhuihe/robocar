
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

#include <gpiorw/gpiorw.h>

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "            GPIORW library demo         " << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // none of anything return
    GPIORW::GPIOLibInit(GPIORW::GFT_WiringPi);
    std::cout << "GPIOLibInit" << std::endl;

    int pin = 37;
    int ret = 0;
    std::cout << "Test GPIO read/write pin " << pin << std::endl;
    ret = GPIORW::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    ret = GPIORW::GPIOWrite(pin, 1);
    std::cout << "GPIOWrite: " << 1 << " return: " << ret << std::endl;
    ret = GPIORW::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    std::cout << std::endl;

    pin = 35;
    ret = 0;
    std::cout << "Test GPIO read/write pin " << pin << std::endl;
    ret = GPIORW::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    ret = GPIORW::GPIOWrite(pin, 1);
    std::cout << "GPIOWrite: " << 1 << " return: " << ret << std::endl;
    ret = GPIORW::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    std::cout << std::endl;

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "eclipsed time " << elapsed.count() << " ms\n";
    std::cout << std::endl;

    GPIORW::GPIOLibRelease();

    std::cout << "Press 'Enter' to exit ...";
    getchar();

    return 0;
}
