
#ifndef BR_HELPER_HPP
#define BR_HELPER_HPP

#include <iostream>
#include "czmq.h"
#include "spdlog/spdlog.h"
#include "_inl.hpp"
#include "DataProcessor.hpp"
#include "PubDataBehavior.hpp"
#include "xmlbus/config_def.hpp"

namespace xmlbus { struct LOG; }
namespace broker
{
    extern std::shared_ptr<spdlog::logger> g_log_;
    class BrHelper
    {
    public:
        BrHelper(std::string id)
            : data_read_proxy(nullptr)
            , data_forward_proxy(nullptr)
            , dp(nullptr)
            , d_pub(nullptr)
        {
            id_ = id;
            g_log_->info("BrHelper constructed");
        }

        ~BrHelper()
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
            url_.broker_in_ = url_recv;
            url_.broker_out_ = "@" + url_send;
            url_.recv_in_ = url_.broker_in_;
            url_.recv_out_ = master ? S_PROXY_RECV_BACKEND : C_PROXY_RECV_BACKEND;
            url_.send_in_ = master ? S_PROXY_SEND_FONTEND : C_PROXY_SEND_FONTEND;
            url_.send_out_ = master ? S_PROXY_SEND_BACKEND : C_PROXY_SEND_BACKEND;
            url_.pub_in_ = master ? S_IPC_PUB_RECV : C_IPC_PUB_RECV;
            url_.pub_out_ = url_.broker_out_;
            set_proxy_url(url_);

            create_data_proxy();
            process_data();
            process_pub_data();
        }

        void stop()
        {
            dp = nullptr;
            d_pub = nullptr;
        }

        void destroy()
        {
            zactor_destroy(&data_read_proxy);
            g_log_->info("data proxy destroyed");
            zactor_destroy(&data_forward_proxy);
            g_log_->info("data pub proxy destroyed");
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
            dp = std::make_shared<data_processor>();
            dp->set_url(p_url);
            dp->start();
        }

        /**
         * @brief worker for receive&publish data
         *
        **/

        void process_pub_data()
        {
            d_pub = std::make_shared<pub_data_behavior>();
            d_pub->set_url(p_url);
            d_pub->start();
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
                zstr_sendx(data_read_proxy, "FRONTEND", "PULL", p_url.recv_in_.c_str(), NULL);
                zsock_wait(data_read_proxy);
                zstr_sendx(data_read_proxy, "BACKEND", "PUSH", p_url.recv_out_.c_str(), NULL);
                zsock_wait(data_read_proxy);
                g_log_->info("data proxy started");
            }

            // 2. proxy forward
            /* another data proxy for publish data*/
            data_forward_proxy = zactor_new(zproxy, NULL);
            if (data_forward_proxy)
            {
                zstr_sendx(data_forward_proxy, "FRONTEND", "PULL", p_url.send_in_.c_str(), NULL);
                zsock_wait(data_forward_proxy);
                zstr_sendx(data_forward_proxy, "BACKEND", "PUSH", p_url.send_out_.c_str(), NULL);
                zsock_wait(data_forward_proxy);
                g_log_->info("data pub proxy started");
            }
        }

    private:
        zactor_t* data_read_proxy;
        zactor_t* data_forward_proxy;
        proxy_url  ;
        std::string id_;
        std::shared_ptr<data_processor> dp;
        std::shared_ptr<pub_data_behavior> d_pub;
    };
}
#endif // !BR_HELPER_HPP
