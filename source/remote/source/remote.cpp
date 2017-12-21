#include <remote/remote.h>
#include <thread>
#include "helper.hpp"

using namespace spdlog::level;
namespace Remote
{
    std::string id_;
    std::shared_ptr<remoteHelper> g_helper_ = nullptr;

    /**
     * @brief
     *     Constructor
     **/
    remote::remote(std::string id)
    {
        id_ = id;
        g_helper_ = std::make_shared<remoteHelper>(id);
    }

    /**
     * @brief
     *     Destructor
     **/
    remote::~remote()
    {
        stop();
        g_helper_ = nullptr;
    }

    /**
     *  @brief
     *     start router
     *  @param [in] server, use the ip which clients will connect
     *  @param [in] url_recv, url_send
     **/
    void remote::start(std::string url_recv, std::string url_send, bool master)
    {
        g_helper_->start(url_recv, url_send, master);
    }

    /**
     *  @brief
     *     stop remote
     **/
    void remote::stop()
    {
        if (g_helper_)
        {
            g_helper_->stop();
            g_helper_->destroy();
        }
    }
} // namespace Remote
