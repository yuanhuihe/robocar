#ifndef YMQ_SOCK_HPP_
#define YMQ_SOCK_HPP_


#include <thread>
#include <iostream>

//#ifdef _UNIX
#include <sys/event.h>
#include <sys/types.h>
//#else
//#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/event.h>
#include <sys/time.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <unistd.h> // for 'close'

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
            return true;
        }

        virtual void stop()
        {
            if(sock_>0)
            {
                close(sock_);
                sock_ = 0;
            }
        }

        virtual int send(char* data, int data_len) = 0;
        virtual int recv(char* buff, int buff_len) = 0;

    protected:
        int sock_;
    };

} // namespace ymq
#endif //!YMQ_SOCK_HPP_