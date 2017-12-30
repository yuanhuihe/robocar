#include <ymq/ymq.h>

namespace ymq
{
    /**************************** proxy/hub **********************************/
    YMQ_API ymq_proxy ymq_new_proxy(int poll_port, int push_port)
    {
        return nullptr;
    }

    YMQ_API ymq_sock ymq_proxy_destory(ymq_proxy& sock)
    {
        return nullptr;
    }
    /**************************** proxy/hub **********************************/


    /**************************** ymq socket **********************************/
    YMQ_API ymq_sock ymq_new_sock(char* url)
    {
        return nullptr;
    }

    YMQ_API ymq_sock ymq_sock_recv(char* buff, int buff_len)
    {
        return nullptr;
    }

    YMQ_API ymq_sock ymq_sock_send(char* data, int data_len)
    {
        return nullptr;
    }

    YMQ_API ymq_sock ymq_sock_destory(ymq_sock& sock)
    {
        return nullptr;
    }
    /**************************** ymq socket **********************************/
    
} // namespace ymq
