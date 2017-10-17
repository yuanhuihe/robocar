#ifndef _BROKER_H_
#define _BROKER_H_

#include <broker/broker_api.h>
#include <string>
namespace xmlbus { class XmlBus; struct LOG; }

namespace broker
{
    class BROKER_API Broker
    {
    public:
        /**
         * @brief
         *      Constructor
         **/
        Broker(std::string id, xmlbus::LOG& log);

        /**
         * @brief
         *	   Destructor
         **/
        virtual ~Broker();

    public:
        /**
         *  @brief
         *     start router
         *  @param [in] server, use the ip which clients will connect
         *  @param [in] url_recv, url_send
         **/
        void start(std::string url_recv, std::string url_send, xmlbus::XmlBus* xml, bool master);

        /**
         *  @brief
         *     stop broker
         **/
        void stop();

        /**
         *  @brief
         *     enable to process data
         *  @param [in] type mean FrameDevType
         *  @param [in] fusion: true need to be fusion
         **/
        void enable_proc(int type, bool fusion);
    };
} // namespace broker

#endif