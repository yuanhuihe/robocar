#include <ymq/ymq.h>
#include "_inl.hpp"
#include "ymq_proxy.hpp"
#include "ymq_listenner.hpp"
#include "ymq_connection.hpp"

namespace ymq
{
    /**************************** proxy/hub **********************************/
    YMQ_API ymq_proxy_t ymq_new_proxy(char* url_poll, char* url_push)
    {
        return new ymq_proxy(url_poll, url_push);
    }

    YMQ_API void ymq_proxy_destory(ymq_proxy_t& sock)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            s->stop();
            delete s;
            sock = nullptr;
        }
    }
    /**************************** proxy/hub **********************************/


    /**************************** ymq socket **********************************/
    YMQ_API ymq_sock_t ymq_new_sock(const char* url)
    {
        //if(url[0] == '@')
        if(url[0] != '>')
        {
            return new ymq_listenner(url);
        }
        else
        {
            return new ymq_connection(url);
        }
    }

    YMQ_API int ymq_sock_recv(ymq_sock_t sock, char* buff, int buff_len)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            return s->recv(buff, buff_len);
        }
        return -1;
    }

    YMQ_API int ymq_sock_recv_ref(ymq_sock_t /*sock*/, char** /*data*/, int* /*len*/)
    {
        // TBD
        return -1;
    }

    YMQ_API int ymq_sock_send(ymq_sock_t sock, char* data, int len)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            return s->send(data, len);
        }
        return -1;
    }
    
    YMQ_API int ymq_set_sock_recv_timeout(ymq_sock_t sock, int timeout)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            return s->set_recv_timeout(timeout);
        }
        return -1;
    }

    YMQ_API int ymq_set_sock_send_timeout(ymq_sock_t sock, int timeout)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            return s->set_send_timeout(timeout);
        }
        return -1;
    }

    YMQ_API void ymq_sock_destory(ymq_sock_t& sock)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            s->stop();
            delete s;
            sock = nullptr;
        }
    }
    /**************************** ymq socket **********************************/
    
} // namespace ymq
