#ifndef YMQ_CONNECTION_HPP_
#define YMQ_CONNECTION_HPP_

#include "_inl.hpp"
#include "ymq_socket.hpp"

#include <sys/types.h>
#include <sys/socket.h>

namespace ymq
{
class ymq_connection : public ymq_socket
{
  public:
    ymq_connection(char* url)
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
    virtual ~ymq_connection()
    {
        stop();
    }

    virtual bool start()
    {
        stop();

        if(!ymq_socket::start()) return false;

        return (is_conn_ = connect());
    }

    virtual void stop()
    {
        ymq_socket::stop();
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
        if(sock_<=0)
        {
            sock_ = socket(PF_INET, SOCK_STREAM, 0);
            if (sock_ == -1)
            {
                std::cerr << "socket()　failed:" << errno << std::endl;
                return false;
            }

            int set = 1;
            setsockopt(sock_, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
        }

        struct sockaddr_in addr;
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = inet_addr(ip_.c_str());

        if (-1 == ::connect(sock_, (sockaddr*)&addr, sizeof(addr)))
        {
            printf("Client: connect() - Failed to connect. errno(%d).\n", errno);
            return false;
        }
        
        int timeout = 1000; // ms
        #ifdef WIN32
        DWORD t = timeout;
        setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&t, sizeof(t));
        #else
        struct timeval tv = {timeout/1000, 0};
        setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
        #endif

        return true;
    }

  private:
    std::string url_;
    std::string ip_;
    int port_;
    bool is_conn_;
};
} // namespace ymq

#endif //!YMQ_CONNECTION_HPP_