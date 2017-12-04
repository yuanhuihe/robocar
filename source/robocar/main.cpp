
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

void showTips(std::vector<Driver::ExecutiveBody*>& executiveList)
{
    std::cout << "Input definitions:" << std::endl;
    std::cout << " -- " << "q" << ": " << "exit this app" << std::endl;
    std::cout << " -- " << "s" << ": " << "stop all executive bodies" << std::endl;
    std::cout << " -- " << "S" << ": " << "show this tips again" << std::endl;
    std::cout << std::endl;
    std::cout << "Executive bodies:" << std::endl;
    for(size_t i=0; i<executiveList.size(); i++)
    {
        std::string body_name = executiveList[i]->getName();
        std::cout << " -- " << i << ": " << body_name << std::endl;

    }
    std::cout << std::endl;
}

void tInputCtrlThead(int& inputCode, int& act_index, int& speed)
{
    while (inputCode != 'q')
    {
        char strInput[100];
        memset(strInput, 0, sizeof(strInput));

        fgets (strInput, 100, stdin);
        int s = strlen(strInput);
        if (s > 0) strInput[s - 1] = 0;

        sscanf(strInput, "", inputCode, act_index, speed);

        // try convert to number
        int numb = atoi(strInput);
        if(0 == numb && strInput[0] != '0')
        {
            // it is a char
            inputCode = strInput[0];
        }
        else
        {
            inputCode = numb;
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
    std::vector<Driver::ExecutiveBody*> executiveList;
    
    // Enum executive bodies
    Driver::ExecutiveBody* body = eSys->enumFirstExecutiveBody();
    while (body)
    {
        // save to list
        executiveList.push_back(body);

        // next
        body = eSys->enumNextExecutiveBody();
    }

    if(executiveList.size()==0)
    {
        Driver::ExecutiveSystem::ReleaseSystem(&eSys);
        std::cout << "No executable body" << std::endl;
        return -1;
    }

    showTips(executiveList);

    std::cout << "There are " << executiveList.size() << " executive bodies to be used" << std::endl;

    // controlling by console inputs
    int preInput = 0;
    int inputCode = 0;
    int act_index = 0;
    int speed = 0;
    std::thread tInputCtrlObj(tInputCtrlThead, std::ref(inputCode), std::ref(act_index), std::ref(speed));

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
        if(inputCode>=0 && inputCode<(int)executiveList.size())
        {
            Driver::ExecutiveBody* executive_body = executiveList[inputCode];
            executive_body->execute(nullptr, speed);
        }
        else if(inputCode=='s')
        {
            for(auto bd:executiveList)
            {
                bd->stop();
            }
        }
        else if(inputCode=='S')
        {
            showTips(executiveList);
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
    eSys->unloadSystem();

    // release system
    Driver::ExecutiveSystem::ReleaseSystem(&eSys);

    tInputCtrlObj.join();

    // time end
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "runtime " << elapsed.count() << " ms\n";

    return 0;
}
