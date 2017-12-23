
#ifndef REMOTE_HELPER_HPP
#define REMOTE_HELPER_HPP

#include <memory>
#include <iostream>
#include "_inl.hpp"
#include "czmq.h"
#include "spdlog/spdlog.h"

namespace Remote
{
    class remoteHelper
    {
    public:
        remoteHelper(std::string id)
            : data_read_proxy(nullptr)
            , data_forward_proxy(nullptr)
        {
            id_ = id;
        }

        ~remoteHelper()
        {
            stop();

#if defined(__WINDOWS__)
            zsys_shutdown();
#endif
        }

        void start(std::string url_recv, std::string url_send, bool master)
        {
            stop();
            proxy_url url_;
            url_.id_ = id_;
            url_.proxy_recver_in_ = url_recv;
            url_.proxy_recver_out_ = master ? SERVER_PROXY_RECV_BACKEND : CLIENT_PROXY_RECV_BACKEND;
            url_.proxy_sender_in_ = master ? SERVER_PROXY_SEND_FONTEND : CLIENT_PROXY_RECV_BACKEND;
            url_.proxy_sender_out_ = "@" + url_send;
            set_proxy_url(url_);

            create_data_proxy();
            process_data();
            process_pub_data();
        }

        void stop()
        {
        }

        void destroy()
        {
            zactor_destroy(&data_read_proxy);
            zactor_destroy(&data_forward_proxy);
        }

        /**
         * @brief proxy url setter
        **/
        void set_proxy_url(proxy_url& url)
        {
            p_url = url;
        }

        /**
         * @brief worker for processing data
         *
        **/

        void process_data()
        {
        }

        /**
         * @brief worker for receive&publish data
         *
        **/

        void process_pub_data()
        {
        }
    private:
        /**
         * @brief create a proxy for push/pull service
         *
         *
         **/

        void create_data_proxy()
        {
            // 1. proxy read
            data_read_proxy = zactor_new(zproxy, NULL);
            if (data_read_proxy)
            {
                zstr_sendx(data_read_proxy, "FRONTEND", "PULL", p_url.proxy_recver_in_.c_str(), NULL);
                zsock_wait(data_read_proxy);
                zstr_sendx(data_read_proxy, "BACKEND", "PUSH", p_url.proxy_recver_out_.c_str(), NULL);
                zsock_wait(data_read_proxy);
            }

            // 2. proxy forward
            /* another data proxy for publish data*/
            data_forward_proxy = zactor_new(zproxy, NULL);
            if (data_forward_proxy)
            {
                zstr_sendx(data_forward_proxy, "FRONTEND", "PULL", p_url.proxy_sender_in_.c_str(), NULL);
                zsock_wait(data_forward_proxy);
                zstr_sendx(data_forward_proxy, "BACKEND", "PUSH", p_url.proxy_sender_out_.c_str(), NULL);
                zsock_wait(data_forward_proxy);
            }
        }

    private:
        zactor_t* data_read_proxy;
        zactor_t* data_forward_proxy;
        proxy_url p_url;
        std::string id_;
    };
}
#endif // !REMOTE_HELPER_HPP
