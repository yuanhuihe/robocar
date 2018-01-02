#ifndef YMQ_PROXY_HPP_
#define YMQ_PROXY_HPP_

#include "ymq_socket.hpp"
#include "sock_kqueue.hpp"
#include <functional>       // std::bind

using namespace std::placeholders;

namespace ymq
{
    class ymq_proxy : public ymq_socket
    {
    public:
        ymq_proxy(int recv_port, int send_port)
        : puller(recv_port)
        , pusher(send_port)
        {
        }
        virtual ~ymq_proxy()
        {
        }

        virtual void start()
        {
            pusher.start();
            puller.start();
            puller.set_received_callback(std::bind(&ymq_proxy::on_received_data, this, _1, _2));
        }
        virtual void stop()
        {
            pusher.stop();
            puller.stop();
        }

    private:
        sock_kqueue puller;
        sock_kqueue pusher;

    private:
        void on_received_data(char* data, int len)
        {
            pusher.send(data, len);
        }
    };

} // namespace ymq
#endif //!YMQ_PROXY_HPP_