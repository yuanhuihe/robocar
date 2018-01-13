﻿#ifndef YMQ_SOCK_HPP_
#define YMQ_SOCK_HPP_


#include <thread>
#include <iostream>

#include <errno.h>
#include <sys/types.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for 'close'
#endif

namespace ymq
{
    class ymq_socket
    {
    public:
        ymq_socket()
        {
            sock_ = 0;
        }

        virtual ~ymq_socket()
        {
        }

        virtual bool start()
        {
            if (sock_ <= 0)
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
            return true;
        }

        virtual void stop()
        {
            if (sock_>0)
            {
#ifdef WIN32
                ::closesocket(sock_);
#else
                ::close(sock_);
#endif
                sock_ = 0;
            }
        }

        virtual int send(char* data, int data_len) = 0;
        virtual int recv(char* buff, int buff_len) = 0;

        int set_recv_timeout(int timeout)
        {
            if (sock_>0 && timeout >= 0)
            {
#ifdef WIN32
                DWORD t = timeout;
                setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, (const char*)&t, sizeof(t));
#else
                struct timeval tv = { timeout / 1000, (timeout % 1000) * 1000 };
                setsockopt(sock_, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
#endif

                return 0;
            }
            return -1;
        }

        int set_send_timeout(int timeout)
        {
            if (sock_>0 && timeout >= 0)
            {
#ifdef WIN32
                DWORD t = timeout;
                setsockopt(sock_, SOL_SOCKET, SO_SNDTIMEO, (const char*)&t, sizeof(t));
#else
                struct timeval tv = { timeout / 1000, (timeout % 1000) * 1000 };
                setsockopt(sock_, SOL_SOCKET, SO_SNDTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
#endif

                return 0;
            }
            return -1;
        }

    protected:
        int sock_;
    };

} // namespace ymq
#endif //!YMQ_SOCK_HPP_