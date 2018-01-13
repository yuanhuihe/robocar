
#ifndef DATA_PROCESSOR_HPP_
#define DATA_PROCESSOR_HPP_

#include <memory>
#include <iostream>
#include <thread>
#include "_inl.hpp"
#include "ProducerConsumerQueue.h"
#include "DataFramePool.h"
#include "spdlog/spdlog.h"
#include "ymq/ymq.h"
using namespace ymq;

namespace Remote
{
    class data_processor
    {
    public:
        data_processor(std::string id)
            :queue_proc_(1024)
        {
            id_ = id;
            running = false;
            obj_recv = nullptr;
            obj_send = nullptr;
        }

        ~data_processor()
        {
            stop();

#if defined(__WINDOWS__)
            zsys_shutdown();
#endif
        }

        void start(std::string url_recv, std::string url_send)
        {
            stop();
            
            running = true;
            obj_recv = new std::thread(&data_processor::sub_data, this, url_recv);
            obj_send = new std::thread(&data_processor::pub_data, this, url_send);

        }

        void stop()
        {
            running = false;
            if(obj_recv)
            {
                obj_recv->join();
                delete obj_recv;
                obj_recv = nullptr;
            }
            if(obj_send)
            {
                obj_send->join();
                delete obj_send;
                obj_send = nullptr;
            }
        }
        
    private:

        /**
         * @brief worker for receive&publish data
         *
        **/

        void sub_data(std::string recv_url)
        {
            //  Connect application sockets to proxy
            std::string url = ">" + recv_url;
            ymq_sock_t recv_scok = ymq_new_sock(url.c_str());
            assert (recv_scok);
            ymq_set_sock_recv_timeout(recv_scok, 1000);

            char* data = new char[4096];
            size_t len = 4096;
            while(running)
            {
                int rc = ymq_sock_recv(recv_scok, data, len);
                if(rc==-1)
                {
                    continue;
                }

                TransFrame* frame = DataFramePool<TransFrame>::SafetyNew(len);
                if (frame)
                {
                    memcpy(frame->data, data, len);
                    frame->len = len;
                    queue_proc_.write(frame);
                    cv.notify_all();
                }
            }
            delete[] data;
        }

        /**
         * @brief worker for receive&publish data
         *
        **/

        void pub_data(std::string send_url)
        {
            //  Connect application sockets to proxy
            std::string url = ">" + send_url;
            ymq_sock_t send_sock = ymq_new_sock (url.c_str());
            assert (send_sock);

            char id[64];
            sprintf(id, "%s", "<Currently not defined>");

            TransFrame* frame = nullptr;
            while(running)
            {
                while(queue_proc_.read(frame))
                {
                    // doing some data processing
                    proc_data(frame);

                    // send to sender proxy
                    ymq_send(send_sock, "sb", id_.c_str(), &frame->data, &frame->len);

                    DataFramePool<TransFrame>::ReleaseFrame(frame);
                }
                
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock);
            }
        }

    private:

        void proc_data(TransFrame* frame)
        {

        }

    private:
        ProducerConsumerQueue<TransFrame*> queue_proc_;
        std::string id_;

        bool running;
        std::mutex mtx;
        std::condition_variable cv;
        std::thread* obj_recv;
        std::thread* obj_send;
    };
}
#endif // !DATA_PROCESSOR_HPP_
