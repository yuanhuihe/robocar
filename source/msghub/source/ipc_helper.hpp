#ifndef _IPC_HELPER_HPP__
#define _IPC_HELPER_HPP__

#include "streamhub/streamhub.h"
#include "_utility.hpp"
#include "_inl.hpp"
#include <thread>
#include <czmq.h>
#include <iostream>
#include "ProducerConsumerQueue.h"

namespace StreamHub
{
    class ipc_helper
    {
    public:
        ipc_helper()
        : running(false)
        , pubObj(nullptr)
        , subObj(nullptr)
        , send_queue(100)
        , recv_queue(100)
        {

        };
        ~ipc_helper()
        {

        };

        bool start(char* groupTag, bool asHost, int& errn)
        {
            stop();            


            sock_send = zsock_new(ZMQ_DEALER);
            sock_recv = zsock_new(ZMQ_DEALER);
            //  Assign the pathname
            assert (sock_send);
            assert (sock_recv);

            // 对于url，如果是host，就用绑定，如果是client，就用连接
            char url[64] = {0};
            sprintf(url, "%stcp://127.0.0.1", asHost?"@":">");            

            // 对于push操作，如果是host，就在send通道上push;相反，如果是client，则在recv上push
            char channel[128] = {0};
            sprintf(channel, "%s:%s", url, asHost?send_channel:recv_channel);
            sock_send = zsock_new_push(channel);
            if (sock_send == nullptr)
            {
                int e = zmq_errno();
                const char* reason = zmq_strerror(e);
                std::cout << reason << std::endl;

                errn = EIPC_CREATE_IPC_FAILED;
                return false;
            }
            std::cout << zsock_type_str(sock_send) << std::endl;

            // 对于pull操作，如果是host，就在recv通道上pull;相反，如果是client，则在send上pull
            sprintf(channel, "%s:%s", url, asHost?recv_channel:send_channel);
            sock_recv = zsock_new_pull(channel);
            if (sock_recv == nullptr)
            {
                int e = zmq_errno();
                const char* reason = zmq_strerror(e);
                std::cout << reason << std::endl;

                errn = EIPC_CREATE_IPC_FAILED;
                return false;
            }
            std::cout << zsock_type_str(sock_recv) << std::endl;
            
            pubObj = new std::thread(std::bind(&ipc_helper::publish, this));
            subObj = new std::thread(std::bind(&ipc_helper::subscrib, this));

            return true;
        };
        
        int send(char* data, int len, int& errn)
        {
            zframe_t* frame = zframe_new(data, len);
            send_queue.write(frame);
            return len;
        };
        
        int recv(char* data, int buffLen, int& errn)
        {
            zframe_t* frame = nullptr;
            recv_queue.read(frame);
            if(frame)
            {
                int size = zframe_size(frame);
                byte* framedata = zframe_data(frame);
                if(size>buffLen)
                {
                    errn = EIPC_TOO_SMALL_BUFFER;
                    memcpy(data, framedata, buffLen);
                }
                else
                {
                    memcpy(data, framedata, size);
                }
                zframe_destroy (&frame);

                return size;
            }
            else
            {
                errn = EIPC_RECVING_DATA_FAILED;
            }

            return 0;
        };

        void stop()
        {
            if(sock_send) zsock_destroy (&sock_send);
            if(sock_recv) zsock_destroy (&sock_recv);

            SafeCloseThread(pubObj, running);
            SafeCloseThread(subObj, running);
        };
    private:
        bool running;

        std::thread* pubObj;
        std::thread* subObj;

        zsock_t* sock_send;
        zsock_t* sock_recv;

        ProducerConsumerQueue<zframe_t*> send_queue;
        ProducerConsumerQueue<zframe_t*> recv_queue;

        void publish()
        {
            zframe_t* frame = nullptr;
            running = true;
            while (running)
            {
                if(send_queue.read(frame))
                {
                    int size = zframe_size(frame);
                    zsock_send(sock_send, "f", frame);
                    zframe_destroy (&frame);
                    continue;
                }
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(SLEEP_100MS));
            }
        }

        void subscrib()
        {
            zframe_t* frame = nullptr;
            running = true;
            while (running)
            {
                int rc = zsock_recv (sock_recv, "f", &frame);
                if(rc==0)
                {
                    recv_queue.write(frame);
                    continue;
                }
                std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(SLEEP_100MS));
            }
        }
        
    };

    
} // namespace StreamHub

#endif // !_IPC_HELPER_HPP__