#ifndef _BSTREAM_HPP__
#define _BSTREAM_HPP__

#include "streamhub/streamhub.h"
#include "_utility.hpp"
#include "_inl.hpp"
#include <thread>
#include <czmq.h>
#include <iostream>
#include "ProducerConsumerQueue.h"

namespace StreamHub
{
    class bstream
    {
    public:
        bstream()
        : running(false)
        , url_push("")
        , url_pull("")
        , pubObj(nullptr)
        , subObj(nullptr)
        , send_queue(100)
        , recv_queue(100)
        {
            sock_send = zsock_new(ZMQ_DEALER);
            sock_recv = zsock_new(ZMQ_DEALER);

            //  Assign the pathname
            assert (sock_send);
            assert (sock_recv);
        };
        virtual ~bstream()
        {
            stop();
        };

        virtual bool start(char* groupTag, int& errn) = 0;
                
        virtual int send(unsigned char* data, int len, int& errn)
        {
            zframe_t* frame = zframe_new(data, len);
            send_queue.write(frame);
            return len;
        };
        
        virtual int recv(unsigned char* data, int buffLen, int& errn)
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

        virtual void stop()
        {
            if(sock_send) zsock_destroy (&sock_send);
            if(sock_recv) zsock_destroy (&sock_recv);

            SafeCloseThread(pubObj, running);
            SafeCloseThread(subObj, running);
        };
        
        int bRunning()
        {
            return running;
        }
        
    protected:
        bool running;

        std::string url_push;
        std::string url_pull;

        std::thread* pubObj;
        std::thread* subObj;
        
        zsock_t* sock_send;
        zsock_t* sock_recv;

        ProducerConsumerQueue<zframe_t*> send_queue;
        ProducerConsumerQueue<zframe_t*> recv_queue;

        bool create(char* url_push, char* url_pull, int& errn)
        {
            stop();

            this->url_push = url_push;
            this->url_pull = url_pull;

            sock_send = zsock_new_push(url_push);
            if (sock_send == nullptr)
            {
                errmsg(errn);
                return false;
            }
            std::cout << zsock_type_str(sock_send) << std::endl;

            sock_recv = zsock_new_pull(url_pull);
            if (sock_recv == nullptr)
            {
                errmsg(errn);
                return false;
            }
            std::cout << zsock_type_str(sock_recv) << std::endl;

            pubObj = new std::thread(std::bind(&bstream::publish, this));
            subObj = new std::thread(std::bind(&bstream::subscrib, this));

            return true;
        };

        const char* errmsg(int& errn)
        {
            int e = zmq_errno();
            const char* reason = zmq_strerror(e);
            std::cout << reason << std::endl;

            errn = EIPC_CREATE_IPC_FAILED;

            return reason;
        }

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

#endif // !_BSTREAM_HPP__