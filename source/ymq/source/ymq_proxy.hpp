#ifndef YMQ_PROXY_HPP_
#define YMQ_PROXY_HPP_

#include "_inl.hpp"
#include "ymq_socket.hpp"
#include "ymq_listenner.hpp"
#include <functional>           // std::bind

namespace ymq
{
    class ymq_proxy : public ymq_socket
    {
    public:
        ymq_proxy(char* url_recv, char* url_send)
        : puller(url_recv)
        , pusher(url_send)
        {
            start();
        }
        virtual ~ymq_proxy()
        {
            stop();
        }

        virtual bool start()
        {
            stop();

            if(!pusher.start()) return false;
            if(!puller.start()) return false;
            puller.set_received_callback(std::bind(&ymq_proxy::on_received_data, this, _1, _2));

            return true;
        }
        virtual void stop()
        {
            pusher.stop();
            puller.stop();
        }

    private:
        ymq_listenner puller;
        ymq_listenner pusher;

    private:
        void on_received_data(char* data, int len)
        {
            pusher.send(data, len);
        }

        virtual int send(char* /*data*/, int /*data_len*/)
        {

        }
        virtual int recv(char* /*buff*/, int /*buff_len*/)
        {
            
        }
    };

} // namespace ymq
#endif //!YMQ_PROXY_HPP_