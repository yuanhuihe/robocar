#ifndef _REMOTE_H_
#define _REMOTE_H_

#include <remote/remote_api.h>
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
        remote(std::string id);

        /**
         * @brief
         *	   Destructor
         **/
        virtual ~remote();

    public:
        /**
         *  @brief
         *     start remote
         *  @param [in] server, use the ip which clients will connect
         *  @param [in] url_recv, url_send
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