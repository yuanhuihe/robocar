
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

void showTips(std::vector<Driver::Action*>& actlist)
{
    std::cout << "Input definitions:" << std::endl;
    std::cout << " -- " << "q" << ": " << "exit this app" << std::endl;
    std::cout << " -- " << "s" << ": " << "show this tips" << std::endl;
    std::cout << std::endl;
    std::cout << "Actions:" << std::endl;
    for(int i=0; i<actlist.size(); i++)
    {
        std::string action = actlist[i]->getName();
        std::cout << " -- " << i << ": " << action << std::endl;
    }
    std::cout << std::endl;
}

void tInputCtrlThead(int& inputCode)
{
    while (inputCode != 'q')
    {
        char strInput[100];
        memset(strInput, 0, sizeof(strInput));

        fgets (strInput, 100, stdin);
        int s = strlen(strInput);
        if (s > 0) strInput[s - 1] = 0;
        inputCode = atoi(strInput);
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
    
    // action list
    std::vector<Driver::Action*> actionList;
    
    // Enum actions
    Driver::Action* action = eSys->enumFirstAction();
    while (action)
    {
        // save to list
        actionList.push_back(action);

        // next action
        action = eSys->enumNextAction();
    }

    if(actionList.size()==0)
    {
        Driver::ExecutiveSystem::ReleaseSystem(&eSys);
        std::cout << "No executable device" << std::endl;
        return -1;
    }

    showTips(actionList);

    std::cout << "There are " << actionList.size() << " actions to be used" << std::endl;

    // reset motors
    for(auto act:actionList)
    {
        if(act->getType()==Driver::AT_Ready)
        {
            act->execute(0);
            break;
        }
    }

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
        if(inputCode>0 && inputCode<actionList.size())
        {
            actionList[inputCode]->execute(10);
        }
        else if(inputCode=='q')
        {
            break;
        }
        else
        {
            std::cout << "Input error" << std::endl;
        }

        // update input
        preInput = inputCode;
    }

    // reset motors
    for(auto act:actionList)
    {
        if(act->getType()==Driver::AT_Ready)
        {
            act->execute(0);
            break;
        }
    }

    // release system
    Driver::ExecutiveSystem::ReleaseSystem(&eSys);

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "runtime " << elapsed.count() << " ms\n";

    return 0;
}
