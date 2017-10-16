
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

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
    
    // device list
    std::vector<WalkDriver::ExecutiveDevice*> motorList;
    
    // Enum executivable devices
    WalkDriver::ExecutiveDevice* motor = wsys->enumFirstExecutiveBody();
    while (motor)
    {
        motorList.push_back(motor);

        // next device
        motor = wsys->enumNextExecutiveBody();
    }

    if(motorList.size()>0)
    {
        while(true)
        {
            std::cout << "Move forward: " << std::endl;
            int i = 0;
            for(auto mot : motorList)
            {
                std::cout << " motor " << std::endl;
                mot->execute(WalkDriver::MT_MoveForward, WalkDriver::SL_Normal);

                i++;
            }

            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(1000));
        }
    }

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "runtime " << elapsed.count() << " ms\n";


    WalkDriver::WalkSystem::ReleaseSystem(&wsys);

    return 0;
}
