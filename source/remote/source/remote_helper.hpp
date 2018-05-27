
#ifndef REMOTE_HELPER_HPP
#define REMOTE_HELPER_HPP

#include <memory>
#include <iostream>
#include "_inl.hpp"
#include <czmq.h>
#include "data_proc.hpp"
#include "spdlog/spdlog.h"

namespace Remote
{
    class remoteHelper
    {
    public:
        remoteHelper(std::string id)
            : dp(id)
            , data_recv_proxy(nullptr)
            , data_send_proxy(nullptr)
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
            url_.proxy_sender_in_ = master ? SERVER_PROXY_SEND_FONTEND : CLIENT_PROXY_SEND_FONTEND;
            url_.proxy_sender_out_ = "@" + url_send;

            set_proxy_url(url_);

            // 1. proxy receier
            /* data proxy for publish data*/
            data_recv_proxy = zactor_new(zproxy, NULL);
            if (data_recv_proxy)
            {
                zstr_sendx(data_recv_proxy, "FRONTEND", "PULL", p_url.proxy_recver_in_.c_str(), NULL);
                zsock_wait(data_recv_proxy);
                zstr_sendx(data_recv_proxy, "BACKEND", "PUSH", p_url.proxy_recver_out_.c_str(), NULL);
                zsock_wait(data_recv_proxy);
            }

            // 2. proxy sender
            /* another data proxy for publish data*/
            data_send_proxy = zactor_new(zproxy, NULL);
            if (data_send_proxy)
            {
                zstr_sendx(data_send_proxy, "FRONTEND", "PULL", p_url.proxy_sender_in_.c_str(), NULL);
                zsock_wait(data_send_proxy);
                zstr_sendx(data_send_proxy, "BACKEND", "PUSH", p_url.proxy_sender_out_.c_str(), NULL);
                zsock_wait(data_send_proxy);
            }

            process_data();
        }

        void stop()
        {
            dp.stop();

            zactor_destroy(&data_recv_proxy);
            zactor_destroy(&data_send_proxy);
        }

    private:
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
            dp.start(p_url.proxy_recver_out_.c_str(), p_url.proxy_sender_in_.c_str());
        }

    private:
        zactor_t* data_recv_proxy;
        zactor_t* data_send_proxy;
        proxy_url p_url;
        std::string id_;

        data_processor dp;
    };
}
#endif // !REMOTE_HELPER_HPP
