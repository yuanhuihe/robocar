#ifndef _REMOTE_H_
#define _REMOTE_H_

#include <remote/remote_api.h>
#include <remote/remote_def.h>
#include <string>

namespace Remote
{
    class REMOTE_API remote
    {
    public:
        /**
         * @brief
         *      Constructor
         **/
        remote();

        /**
         * @brief
         *	   Destructor
         **/
        virtual ~remote();

    public:
        /**
         *  @brief
         *     start remote
         *  @param [in] url_recv, receive channel
         *  @param [in] url_send, send channel
         *  @param [in] master, wether running as server or client
         **/
        void start(std::string url_recv, std::string url_send, bool master);

        /**
         *  @brief
         *     stop remote
         **/
        void stop();
    };
} // namespace Remote

#endif