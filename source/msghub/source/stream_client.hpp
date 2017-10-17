#ifndef _STREAM_CLIENT_HPP__
#define _STREAM_CLIENT_HPP__

#include "bstream.hpp"

namespace StreamHub
{
    class stream_client: public bstream
    {
    public:
        stream_client()
        {

        };
        ~stream_client()
        {

        };

        virtual bool start(char* groupTag, int& errn)
        {
            // client用连接
            char url[64] = {0};
            sprintf(url, ">tcp://127.0.0.1");            

            // 对于push操作，client在recv通道上push
            char url_push[128] = {0};
            sprintf(url_push, "%s:%s", url, recv_channel);
            
            // 对于pull操作，client在send通道上pull
            char url_pull[128] = {0};
            sprintf(url_pull, "%s:%s", url, send_channel);
            
            return bstream::create(url_push, url_pull, errn);
        };
    };

    
} // namespace StreamHub

#endif // !_STREAM_CLIENT_HPP__