#ifndef YMQ_CONNECTION_HPP_
#define YMQ_CONNECTION_HPP_

#include "ymq_socket.hpp"

#include <sys/types.h>
#include <sys/socket.h>

namespace ymq
{
class ymq_connection : public ymq_socket
{
    #define MAX_RECV_BUFF_SIZE  65535
  public:
    ymq_connection(char* url)
    : url_(url)
    {
        this->sock_ = -1;
        this->running_ = false;
        this->obj_thread_ = nullptr;
        fn_received_data_ = nullptr;

        int p = url_.rfind(':');
        ip_ = url_.substr(0, p);

        std::string str_port = url_.substr(p, url_.length()-p);
        port_ = atoi(str_port.c_str());
    }
    virtual ~ymq_connection()
    {
        stop();
    }

    void set_received_callback(fn_received_data_handle fn)
    {
        fn_received_data_ = fn;
    }

    void start()
    {
        stop();

        /* Start events thread */
        obj_thread_ = new std::thread(&ymq_connection::process, this);
    }

    void stop()
    {
        running_ = false;
        if (obj_thread_)
        {
            obj_thread_->join();
            delete obj_thread_;
            obj_thread_ = nullptr;
        }

        if(sock_>0)
        {
            close(sock_);
            sock_ = 0;
        }
    }

    virtual int send(char* data, int data_len)
    {
        ::send(sock_, data, data_len, 0);
    }

    virtual int recv(char* buff, int buff_len)
    {

    }

  private:
    void process()
    {
        char* buff = new char[MAX_RECV_BUFF_SIZE];
        int len = 0;
        while (running_)
        {
            if(sock_<=0)
            {
                sock_ = connect();
                usleep(1000000);
                continue;
            }

            len = ::recv(sock_, buff, MAX_RECV_BUFF_SIZE, NULL);
            if(len == -1)
            {
                close(sock_);
                sock_ = -1;
                continue;
            }

            if(fn_received_data_)
            {
                fn_received_data_(buff, len);
            }
        }

        delete buff;
    }

    int connect()
    {
        int sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "socket()　failed:" << errno << std::endl;
            return -1;
        }

        int set = 1;
        setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));

        struct sockaddr_in addr;
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port_);
        addr.sin_addr.s_addr = inet_addr(ip_.c_str());

        if (-1 == ::connect(sock, (sockaddr*)&addr, sizeof(addr)))
        {
            printf("Client: connect() - Failed to connect.\n");
            return -1;
        }
        
        struct timeval tv = {5, 0};
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));

        return sock;
    }

  private:
    std::string url_;
    std::string ip_;
    int port_;
    bool running_;
    int sock_;
    fn_received_data_handle fn_received_data_;
    std::thread *obj_thread_;


};
} // namespace ymq

#endif //!YMQ_CONNECTION_HPP_