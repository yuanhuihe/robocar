
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

#include <fsgpio/fsgpio.h>

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "            FSGPIO library demo         " << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // none of anything return
    FSGPIO::GPIOLibInit();
    std::cout << "GPIOLibInit" << std::endl;

    int pin = 37;
    int ret = 0;
    std::cout << "Test GPIO read/write pin " << pin << std::endl;
    ret = FSGPIO::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    ret = FSGPIO::GPIOWrite(pin, 1);
    std::cout << "GPIOWrite: " << 1 << " return: " << ret << std::endl;
    ret = FSGPIO::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    std::cout << std::endl;

    pin = 35;
    ret = 0;
    std::cout << "Test GPIO read/write pin " << pin << std::endl;
    ret = FSGPIO::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    ret = FSGPIO::GPIOWrite(pin, 1);
    std::cout << "GPIOWrite: " << 1 << " return: " << ret << std::endl;
    ret = FSGPIO::GPIORead(pin);
    std::cout << "GPIORead: " << ret << std::endl;
    std::cout << std::endl;

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "eclipsed time " << elapsed.count() << " ms\n";
    std::cout << std::endl;


    FSGPIO::GPIOLibRelease();

    std::cout << "Press 'Enter' to exit ...";
    getchar();

    return 0;
}
