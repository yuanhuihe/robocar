#ifndef RMQ_PROXY_HPP_
#define RMQ_PROXY_HPP_

#include "_inl.hpp"
#include "rmq_socket.hpp"
#include "rmq_listenner.hpp"
#include <functional>           // std::bind

namespace rmq
{
    class rmq_proxy : public rmq_socket
    {
    public:
        rmq_proxy(char* url_recv, char* url_send)
        : puller(url_recv)
        , pusher(url_send)
        {
            start();
        }
        virtual ~rmq_proxy()
        {
            stop();
        }

        virtual bool start()
        {
            stop();

            if(!pusher.start()) return false;
            if(!puller.start()) return false;
            puller.set_received_callback(std::bind(&rmq_proxy::on_received_data, this, _1, _2));

            return true;
        }
        virtual void stop()
        {
            pusher.stop();
            puller.stop();
        }

    private:
        rmq_listenner puller;
        rmq_listenner pusher;

    private:
        void on_received_data(char* data, int len)
        {
            pusher.send(data, len);
        }

        virtual int send(char* /*data*/, int /*data_len*/)
        {
            return -1;
        }
        virtual int recv(char* /*buff*/, int /*buff_len*/)
        {
            return -1;
        }
    };

} // namespace rmq
#endif //!RMQ_PROXY_HPP_