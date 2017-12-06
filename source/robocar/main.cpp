
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <stdio.h>  // for fgets()
#include <tuple>
#include <string>       // std::string
#include <string.h>     // memxxx/strlen()

#include <executive/executive.h>

void showTips(std::vector<Driver::Action*>& actList)
{
    std::cout << "*************************************************" << std::endl;
    std::cout << "Input definitions:" << std::endl;
    std::cout << " -- " << "q" << ": " << "exit this app" << std::endl;
    std::cout << " -- " << "s" << ": " << "show this tips again" << std::endl;
    std::cout << std::endl;
    std::cout << "Format for running an action: " << std::endl;
    std::cout << " Run action : 'action index' + 'speed'" << std::endl;
    std::cout << " Stop action: 'action index' + 's'" << std::endl;
    std::cout << " e.g.: 1 70 ==> run action '1' with speed of '70%'" << std::endl;
    std::cout << std::endl;
    std::cout << "Actions list:" << std::endl;
    for (size_t i = 0; i<actList.size(); i++)
    {
        std::string name = actList[i]->getName();
        std::cout << " -- " << i << ": " << name << std::endl;

    }

    std::cout << "There are " << actList.size() << " actions can be executed" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << std::endl;
}

void tInputCtrlThead(int& code, int& speed)
{
    while (code != 'q')
    {
        char strInput[100];
        memset(strInput, 0, sizeof(strInput));

        fgets(strInput, 100, stdin);
        int s = strlen(strInput);
        if (s > 0) strInput[s - 1] = 0;

        int ret = sscanf(strInput, "%d %d", &code, &speed);
        switch (ret)
        {
        case 0:
        {
            // No any number input, maybe 's' or 'q' input
            code = strInput[0];
        }
        break;
        case 1:
        {
            // maybe input action stop command: number + 's'
            ret = sscanf(strInput, "%d %c", &code, &speed);
            if (ret != 2)
            {
                ret = sscanf(strInput, "%c %d", &code, &speed);
            }
        }
        break;
        case 2:
        {
            // no input error
        }
        break;
        default:
            break;
        }
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "           robocar application          " << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // get system instance
    Driver::ExecutiveSystem* eSys = Driver::ExecutiveSystem::InitSystem();

    // load system
    eSys->loadSystem();

    // ExecutiveB body list
    std::vector<Driver::Action*> actionList;

    // Enum all actions
    Driver::Action* act = eSys->enumFirstAction();
    while (act)
    {
        // save to list
        actionList.push_back(act);
        // next
        act = eSys->enumNextAction();
    }

    if (actionList.size() == 0)
    {
        Driver::ExecutiveSystem::ReleaseSystem(&eSys);
        std::cout << "No executable actions on this system" << std::endl;
        return -1;
    }

    // reset to standby state
    eSys->resetSystem();

    showTips(actionList);

    // controlling by console inputs
    int preInput = 0;
    int preSpeed = 0;
    int inputCode = 0;
    int inputSpeed = 0;
    std::thread tInputCtrlObj(tInputCtrlThead, std::ref(inputCode), std::ref(inputSpeed));

    bool bRunning = true;
    while (bRunning)
    {
        // check input
        if (inputCode == preInput && preSpeed == inputSpeed)
        {
            std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(50));
            continue;
        }

        // execute action
        if (inputCode >= 0 && inputCode<(int)actionList.size() && preSpeed != inputSpeed)
        {
            if (inputSpeed != 's')
            {
                eSys->runAction(actionList[inputCode], inputSpeed);
            }
            else
            {
                eSys->stopAction(actionList[inputCode]);
            }
        }
        else if (inputCode == 's')
        {
            showTips(actionList);
        }
        else if (inputCode == 'q')
        {
            break;
        }
        else
        {
            std::cout << "Input error" << std::endl;
        }

        // update input
        preInput = inputCode;
        preSpeed = inputSpeed;
    }

    eSys->resetSystem();

    // reset motors
    eSys->unloadSystem();

    // release system
    Driver::ExecutiveSystem::ReleaseSystem(&eSys);

    tInputCtrlObj.join();

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "runtime " << elapsed.count() << " ms\n";

    return 0;
}
