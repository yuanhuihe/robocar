#ifndef _STREAM_SERVER_HPP__
#define _STREAM_SERVER_HPP__

#include "bstream.hpp"

namespace StreamHub
{
    class stream_server : public bstream
    {
    public:
        stream_server()
        {

        };
        ~stream_server()
        {

        };

        virtual bool start(char* groupTag, int& errn)
        {
            // host用绑定
            char url[64] = { 0 };
            sprintf(url, "@tcp://127.0.0.1");

            // 对于push操作，host在send通道上push
            char url_push[128] = { 0 };
            sprintf(url_push, "%s:%s", url, send_channel);
            
            // 对于pull操作，host在recv通道上pull
            char url_pull[128] = { 0 };
            sprintf(url_pull, "%s:%s", url, recv_channel);
            
            return bstream::create(url_push, url_pull, errn);
        };
    private:

    };

    
} // namespace StreamHub

#endif // !_STREAM_SERVER_HPP__