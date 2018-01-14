#include <rmq/rmq.h>
#include "_inl.hpp"
#include "rmq_proxy.hpp"
#include "rmq_listenner.hpp"
#include "rmq_connection.hpp"

namespace rmq
{
    /**************************** proxy/hub **********************************/
    RMQ_API rmq_proxy_t rmq_new_proxy(char* url_poll, char* url_push)
    {
        return new rmq_proxy(url_poll, url_push);
    }

    RMQ_API void rmq_proxy_destory(rmq_proxy_t& sock)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            s->stop();
            delete s;
            sock = nullptr;
        }
    }
    /**************************** proxy/hub **********************************/


    /**************************** rmq socket **********************************/
    RMQ_API rmq_sock_t rmq_new_sock(const char* url)
    {
        //if(url[0] == '@')
        if(url[0] != '>')
        {
            return new rmq_listenner(url);
        }
        else
        {
            return new rmq_connection(url);
        }
    }

    RMQ_API int rmq_sock_recv(rmq_sock_t sock, char* buff, int buff_len)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            return s->recv(buff, buff_len);
        }
        return -1;
    }

    RMQ_API int rmq_sock_recv_ref(rmq_sock_t /*sock*/, char** /*data*/, int* /*len*/)
    {
        // TBD
        return -1;
    }

    RMQ_API int rmq_sock_send(rmq_sock_t sock, char* data, int len)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            return s->send(data, len);
        }
        return -1;
    }
    
    RMQ_API int rmq_set_sock_recv_timeout(rmq_sock_t sock, int timeout)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            return s->set_recv_timeout(timeout);
        }
        return -1;
    }

    RMQ_API int rmq_set_sock_send_timeout(rmq_sock_t sock, int timeout)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            return s->set_send_timeout(timeout);
        }
        return -1;
    }

    RMQ_API void rmq_sock_destory(rmq_sock_t& sock)
    {
        rmq_socket* s = static_cast<rmq_socket*>(sock);
        if(s)
        {
            s->stop();
            delete s;
            sock = nullptr;
        }
    }
    /**************************** rmq socket **********************************/
    
} // namespace rmq
