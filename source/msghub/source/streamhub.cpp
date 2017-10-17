#include "streamhub/streamhub.h"
#include "_utility.hpp"
#include "_inl.hpp"
#include "bstream.hpp"
#include "stream_client.hpp"
#include "stream_server.hpp"

namespace StreamHub
{
    bstream* g_helper = nullptr;
    StreamDataReceivedCallback fnStreamDataReceived = nullptr;

    STREAMHUB_API void setStreamDataReceivedCallback(void* userData, StreamDataReceivedCallback handle)
    {
        fnStreamDataReceived = handle;
    }

    STREAMHUB_API int start(char* groupTag, bool asHost, int& errn)
    {
        if (asHost)
        {
            g_helper = new stream_server();
        }
        else
        {
            g_helper = new stream_client();
        }
        
        g_helper->start(groupTag, errn);
        
        return errn;
    }

    STREAMHUB_API void stop(int& errn)
    {
        if (g_helper)
        {
            g_helper->stop();
            SafeDelete(g_helper);
        }
    }

    STREAMHUB_API int bRunning()
    {
        if (g_helper)
        {
            return g_helper->bRunning();
        }

        return 0;
    }

    STREAMHUB_API int send(unsigned char* data_stream, int stream_size, int& errn)
    {
        if (g_helper)
        {
            return g_helper->send(data_stream, stream_size, errn);
        }

        return -1;
    }
    
    STREAMHUB_API int read(unsigned char* data_buffer, int buffer_size, int& errn)
    {
        if (g_helper)
        {
            return g_helper->recv(data_buffer, buffer_size, errn);
        }

        return -1;
    }

    
} // namespace StreamHub
