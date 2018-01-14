#ifndef REMOTE_HPP_
#define REMOTE_HPP_

#include <string.h>
#include <iostream>
#include <thread>

#include <ProducerConsumerQueue.h>
#include <rmq/rmq.h>
using namespace rmq;

class Remote
{
public:
    Remote()
    : is_running_(false)
    , proxy_(nullptr)
    , sock_push_(nullptr)
    , sock_pull_(nullptr)
    , obj_send_(nullptr)
    , obj_recv_(nullptr)
    , recv_queu_(1024)
    , send_queu_(1024)
    {

    }
    ~Remote()
    {

    }

    bool start()
    {
        stop();

        int recv_port = 7788;
        int send_port = 7799;

        char url_recv[64];
        char url_send[64];
        sprintf(url_recv, "@tcp://*:%d", recv_port);
        sprintf(url_send, "@tcp://*:%d", send_port);

        std::cout << "Creating proxy:\n puller: " << url_recv << "\n pusher: " << url_send << std::endl;
        proxy_ = rmq_new_proxy(url_recv, url_send);

        char url_push[64];
        sprintf(url_push, ">tcp://127.0.0.1:%d", recv_port);
        std::cout << "Creating a connection to " << url_push << std::endl;
        sock_push_ = rmq_new_sock((char*)url_push);

        char url_pull[64];
        sprintf(url_pull, ">tcp://127.0.0.1:%d", send_port);
        std::cout << "Creating a connection to " << url_pull << std::endl;
        sock_pull_ = rmq_new_sock((char*)url_pull);

        is_running_ = true;
        obj_send_ = new std::thread(&Remote::remote_send, this);
        obj_recv_ = new std::thread(&Remote::remote_recv, this);

        return true;
    }

    void stop()
    {
        is_running_ = false;

        if(obj_send_){obj_send_->join();delete obj_send_; obj_send_ = nullptr;}
        if(obj_recv_){obj_recv_->join();delete obj_recv_; obj_recv_ = nullptr;}

        rmq_proxy_destory(proxy_);
        rmq_sock_destory(sock_push_);
        rmq_sock_destory(sock_pull_);
    }

    int send(char* data, int len)
    {

    }

    int recv(char* buff, int buff_len)
    {

    }

private:
    void remote_send()
    {
        rmq_frame_t frame;
        int header_len = sizeof(rmq_frame_header_t);
        while(is_running_)
        {
            if(send_queu_.read(frame))
            {
                rmq_sock_send(sock_push_, (char*)&frame, header_len + frame.header.data_len);
            }
            else
            {
                cv_wait();
            }
        }
    };

    void remote_recv()
    {
        rmq_set_sock_recv_timeout(sock_pull_, 1000);
        rmq_frame_t frame;
        while(is_running_)
        {
            if(-1 == rmq_sock_recv(sock_pull_, (char*)&frame, sizeof(frame)))
            {
                continue;
            }

            recv_queu_.write(frame);
            cv_notify();
        }
    };

    void cv_wait()
    {

    }

    void cv_notify()
    {

    }
private:
    bool is_running_;
    rmq_proxy_t proxy_;
    rmq_sock_t sock_push_;
    rmq_sock_t sock_pull_;

    std::thread* obj_send_;
    std::thread* obj_recv_;
    
    ProducerConsumerQueue<rmq_frame_t> recv_queu_;
    ProducerConsumerQueue<rmq_frame_t> send_queu_;
};


#endif //!REMOTE_HPP_