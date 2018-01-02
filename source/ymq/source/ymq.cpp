#include <ymq/ymq.h>
#include "ymq_proxy.hpp"
#include "ymq_listernner.hpp"
#include "ymq_connection.hpp"

namespace ymq
{
    /**************************** proxy/hub **********************************/
    YMQ_API ymq_proxy_t ymq_new_proxy(int poll_port, int push_port)
    {
        return new ymq_proxy(poll_port, push_port);
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
    YMQ_API ymq_sock_t ymq_new_sock(char* url)
    {
        //if(url[0] == '@')
        if(url[0] != '>')
        {
            return new ymq_listernner(url);
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

    YMQ_API int ymq_sock_send(ymq_sock_t sock, char* data, int data_len)
    {
        ymq_socket* s = static_cast<ymq_socket*>(sock);
        if(s)
        {
            return s->send(data, data_len);
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
