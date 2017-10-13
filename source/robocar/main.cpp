
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>

#include <walkdriver/walkdriver.h>

int main(int /*argc*/, char* /*argv*/[])
{
    // Calculate and print fibonacci number
    std::cout << "walkdriver library" << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // get system instance
    WalkDriver::WalkSystem* wsys = WalkDriver::WalkSystem::InitSystem(WalkDriver::CT_MotorSystem);
    
    
    // Enum executivable devices
    WalkDriver::ExecutiveDevice* motor = wsys->enumExecutiveBody();
    while (motor)
    {


        // next device
        motor = wsys->enumExecutiveBody();
    }

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "runtime " << elapsed.count() << " ms\n";


    WalkDriver::WalkSystem::ReleaseSystem(&wsys);

    return 0;
}
