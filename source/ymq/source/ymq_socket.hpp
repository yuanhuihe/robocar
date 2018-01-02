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
    typedef std::function<void(char*, int)> fn_received_data_handle;

    class ymq_socket
    {
    public:
        ymq_socket()
        {
        }
        virtual ~ymq_socket()
        {
        }

        virtual void start()
        {

        }
        virtual void stop()
        {

        }

        virtual int send(char* data, int data_len)
        {

        }

        virtual int recv(char* buff, int buff_len)
        {

        }

    private:

    };

} // namespace ymq
#endif //!YMQ_SOCK_HPP_