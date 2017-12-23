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
    remote::remote()
    {
        g_helper_ = std::make_shared<remoteHelper>(id_);
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
    *  @param [in] url_recv, receive channel
    *  @param [in] url_send, send channel
    *  @param [in] master, wether running as server or client
    **/
    void remote::start(/*std::string url_recv, std::string url_send, */bool master)
    {
        g_helper_->start(SERVER_RECV_URL, SERVER_SEND_URL, master);
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
