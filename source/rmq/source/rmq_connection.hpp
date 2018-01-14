#ifndef RMQ_CONNECTION_HPP_
#define RMQ_CONNECTION_HPP_

#include "_inl.hpp"
#include "rmq_socket.hpp"

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

namespace rmq
{
class rmq_connection : public rmq_socket
{
  public:
    rmq_connection(const char* url)
    : url_(url)
    {
        this->is_conn_ = false;

        url_ = url;
        int p1 = url_.rfind('/') + 1;
        int p2 = url_.rfind(':');
        ip_ = url_.substr(p1, p2-p1);

        p2 += 1;
        std::string str_port = url_.substr(p2, url_.length()-p2);
        port_ = atoi(str_port.c_str());

        start();
    }
    virtual ~rmq_connection()
    {
        stop();
    }

    virtual bool start()
    {
        stop();

        if(!rmq_socket::start()) return false;

        return (is_conn_ = connect());
    }

    virtual void stop()
    {
        rmq_socket::stop();
    }

    virtual int send(char* data, int data_len)
    {
        return ::send(sock_, data, data_len, 0);
    }

    virtual int recv(char* buff, int buff_len)
    {
        return ::recv(sock_, buff, buff_len, 0);
    }

  private:
    bool connect()
    {
        struct sockaddr_in addr;
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = inet_addr(ip_.c_str());
        /* Set all bits of the padding field to 0 */
        memset(addr.sin_zero, '\0', sizeof addr.sin_zero);  

        if (-1 == ::connect(sock_, (sockaddr*)&addr, sizeof(addr)))
        {
            int errnum = errno;
            printf("Client: connect() - %s(errno=%d).\n", strerror(errnum), errnum);
            return false;
        }

        return true;
    }

  private:
    std::string url_;
    std::string ip_;
    int port_;
    bool is_conn_;
};
} // namespace rmq

#endif //!RMQ_CONNECTION_HPP_