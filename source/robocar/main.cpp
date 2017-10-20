
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <stdio.h>  // for fgets()
#include <tuple>
#include <string>       // std::string
#include <string.h>     // memxxx/strlen()

#include <walkdriver/walkdriver.h>

std::tuple<int, std::string, std::string> actionMap[] =
{
    {0, "stop", "Stop"},
    {1, "foreward", "Move Foreward"},
    {2, "leftward", "Move Leftward"},
    {3, "rightward", "Move Rightward"},
    {4, "backward", "Move Backward"},
    {5, "tips", "Tips"},
    {6, "exit", "Exit this program"},
};

void showTips()
{
    std::cout << "Input definitions:" << std::endl;
    for(auto item: actionMap)
    {
        int code = std::get<0>(item);
        std::string action = std::get<2>(item);
        std::cout << " -- " << code << ": " << action << std::endl;
    }
}

void tInputCtrlThead(int& inputCode)
{
    while (inputCode != 6)
    {
        char strInput[100];
        memset(strInput, 0, sizeof(strInput));

        fgets (strInput, 100, stdin);
        int s = strlen(strInput);
        if (s > 0) strInput[s - 1] = 0;

        bool bOK = false;
        for (auto act : actionMap)
        {
            int code = atoi(strInput);
            if (code == std::get<0>(act) || strcmp(strInput, std::get<1>(act).c_str()) == 0)
            {
                inputCode = std::get<0>(act);
                bOK = true;
                //std::cout << std::get<2>(act) << std::endl;                
                break;
            }
        }

        if (!bOK)
        {
            std::cout << "Input error" << std::endl;
        }
    }
}

void actionMoveForeward(std::vector<WalkDriver::ExecutiveDevice*>& motorList)
{
    std::cout << std::endl << "Running Move foreward: " << std::endl;
    for(auto mot : motorList)
    {
        mot->execute(WalkDriver::MT_MoveForward, WalkDriver::SL_Normal);
    }
    std::cout << "Down " << std::endl;
}
void actionMoveLeftward(std::vector<WalkDriver::ExecutiveDevice*>& motorList)
{
    std::cout << std::endl << "Running Move leftward: " << std::endl;
    for(int i=0; i<motorList.size(); i++)
    {
        motorList[i]->execute(WalkDriver::MT_MoveForward, i != 0 ? WalkDriver::SL_Normal : WalkDriver::SL_Stop);
    }
    std::cout << "Down " << std::endl;
}
void actionMoveRightward(std::vector<WalkDriver::ExecutiveDevice*>& motorList)
{
    std::cout << std::endl << "Running Move rightward: " << std::endl;
    for (int i = 0; i<motorList.size(); i++)
    {
        motorList[i]->execute(WalkDriver::MT_MoveForward, i != 1 ? WalkDriver::SL_Normal : WalkDriver::SL_Stop);
    }
    std::cout << "Down " << std::endl;
}
void actionMoveBackward(std::vector<WalkDriver::ExecutiveDevice*>& motorList)
{
    std::cout << std::endl << "Running Move leftward: " << std::endl;
    for (int i = 0; i<motorList.size(); i++)
    {
        motorList[i]->execute(WalkDriver::MT_MoveBackward, WalkDriver::SL_Normal);
    }
    std::cout << "Down " << std::endl;
}
void actionMoveStop(std::vector<WalkDriver::ExecutiveDevice*>& motorList)
{
    std::cout << std::endl << "Running Action 'Stop': " << std::endl;
    for (int i = 1; i<motorList.size(); i++)
    {
        motorList[i]->execute(WalkDriver::MT_MoveForward, WalkDriver::SL_Stop);
    }
    std::cout << "Down " << std::endl;
}

int main(int /*argc*/, char* /*argv*/[])
{
    // Calculate and print fibonacci number
    std::cout << "           robocar application          " << std::endl;
    std::cout << "========================================" << std::endl;

    showTips();

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
    std::cout << "There are " << motorList.size() << " motors to be used to controlling" << std::endl;

    if(motorList.size()==0)
    {
        WalkDriver::WalkSystem::ReleaseSystem(&wsys);
        std::cout << "No executable device" << std::endl;
        return -1;
    }

    // reset motors
    actionMoveStop(motorList);

    // controlling by console inputs
    int preInput = 0;
    int inputCode = 0;
    std::thread tInputCtrlObj(tInputCtrlThead, std::ref(inputCode));

    bool bRunning = true;
    while(bRunning)
    {
        // check input
        if(inputCode == preInput)
        {
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(50));
            continue;
        }

        // execute action
        switch(inputCode)
        {
            case 0: actionMoveStop(motorList); break;
            case 1: actionMoveForeward(motorList); break;
            case 2: actionMoveLeftward(motorList); break;
            case 3: actionMoveRightward(motorList); break;
            case 4: actionMoveBackward(motorList); break;
            case 5: showTips(); break;
            case 6: bRunning = false; break;
            default: break;
        }

        // update input
        preInput = inputCode;
    }

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "runtime " << elapsed.count() << " ms\n";

    tInputCtrlObj.join();

    // reset motors
    actionMoveStop(motorList);

    WalkDriver::WalkSystem::ReleaseSystem(&wsys);

    return 0;
}
