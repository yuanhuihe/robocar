
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

#include <ymq/ymq.h>
using namespace ymq;

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "            ymq library demo            " << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    int puller_port = 7788;
    int pusher_port = 7799;
    std::cout << "Creating proxy at " << puller_port << ":" << pusher_port << std::endl;
    ymq_proxy_t proxy = ymq_new_proxy(puller_port, pusher_port);

    char url_push[64];
    sprintf(url_push, ">tcp://127.0.0.1:%d", puller_port);
    std::cout << "Creating a connection to " << url_push << std::endl;
    ymq_sock_t sock_push = ymq_new_sock((char*)url_push);

    char url_pull[64];
    sprintf(url_pull, ">tcp://127.0.0.1:%d", pusher_port);
    std::cout << "Creating a connection to " << url_pull << std::endl;
    ymq_sock_t sock_pull = ymq_new_sock((char*)url_pull);

    auto fn_send = [&sock_push]()
    {
        int cnt = 1000000;
        char buff[10240];
        while(cnt>0)
        {
            ymq_sock_send(sock_push, buff, sizeof(buff));



            cnt--;
        }
    };

    auto fn_recv = [&sock_pull]()
    {
        int cnt = 1000000;
        char buff[10240];
        while(cnt>0)
        {
            ymq_sock_recv(sock_pull, buff, sizeof(buff));

            cnt--;
        }
    };

    std::thread obj_send(fn_send);
    std::thread obj_recv(fn_recv);

    obj_send.join();
    obj_recv.join();

    ymq_proxy_destory(proxy);
    ymq_sock_destory(sock_push);
    ymq_sock_destory(sock_pull);

    getchar();

    return 0;
}
