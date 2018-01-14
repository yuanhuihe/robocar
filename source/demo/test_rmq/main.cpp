
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

#include <rmq/rmq.h>
using namespace rmq;

int main(int /*argc*/, char* /*argv*/[])
{
    std::cout << "            rmq library demo            " << std::endl;
    std::cout << "========================================" << std::endl;

    // time start
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    int recv_port = 7788;
    int send_port = 7799;

    char url_recv[64];
    char url_send[64];
    sprintf(url_recv, "@tcp://*:%d", recv_port);
    sprintf(url_send, "@tcp://*:%d", send_port);

    std::cout << "Creating proxy:\n puller: " << url_recv << "\n pusher: " << url_send << std::endl;
    rmq_proxy_t proxy = rmq_new_proxy(url_recv, url_send);

    char url_push[64];
    sprintf(url_push, ">tcp://127.0.0.1:%d", recv_port);
    std::cout << "Creating a connection to " << url_push << std::endl;
    rmq_sock_t sock_push = rmq_new_sock((char*)url_push);

    char url_pull[64];
    sprintf(url_pull, ">tcp://127.0.0.1:%d", send_port);
    std::cout << "Creating a connection to " << url_pull << std::endl;
    rmq_sock_t sock_pull = rmq_new_sock((char*)url_pull);

    auto fn_send = [&sock_push]()
    {
        int cnt = 1000;
        char buff[1024];
        while(cnt>0)
        {
            rmq_sock_send(sock_push, buff, sizeof(buff));
            cnt--;
        }
    };

    auto fn_recv = [&sock_pull]()
    {
        rmq_set_sock_recv_timeout(sock_pull, 5000);
        char buff[1024];
        while(true)
        {
            if(-1 == rmq_sock_recv(sock_pull, buff, sizeof(buff)))
            {
                break;
            }
        }
    };

    std::thread obj_send(fn_send);
    std::thread obj_recv(fn_recv);

    obj_send.join();
    obj_recv.join();

    rmq_proxy_destory(proxy);
    rmq_sock_destory(sock_push);
    rmq_sock_destory(sock_pull);

    return 0;
}
