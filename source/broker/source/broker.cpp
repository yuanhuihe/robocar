#include <broker/broker.h>
#include <thread>
#include "broker/brhelper.hpp"
#include "_inl.hpp"
#include "DataFusion.h"
#include "DataHelper.h"
#include "XmlBus.h"

using namespace spdlog::level;
namespace broker
{
    std::string id_;
    xmlbus::LOG log_;
    std::shared_ptr<spdlog::logger> g_log_ = nullptr;
    std::shared_ptr<BrHelper> g_helper_ = nullptr;

    /**
     * @brief
     *     Constructor
     **/
    Broker::Broker(std::string id, xmlbus::LOG& log)
    {
        id_ = id;
        if (!g_log_)
        {
            log_ = log;
            std::string filename = log.path + log.name + Suffix_Log;
            spdlog::set_async_mode(8192);
            g_log_ = spdlog::rotating_logger_mt(log.name.c_str(), filename, 1024 * 1024 * 5, 50);
            g_log_->set_level(static_cast<level_enum>(log.level_));
            g_log_->flush_on(static_cast<level_enum>(log.level_));
        }
        g_helper_ = std::make_shared<BrHelper>(id);
        g_log_->info("[Broker] constructed.");
    }

    /**
     * @brief
     *     Destructor
     **/
    Broker::~Broker()
    {
        stop();
        g_log_->info("[Broker] destructed.");

        // 删除日志
        spdlog::drop(log_.name);
        g_log_->~logger();
        g_log_ = nullptr;

        // 释放BrHelper
        g_helper_ = nullptr;
    }

    /**
     *  @brief
     *     start router
     *  @param [in] server, use the ip which clients will connect
     *  @param [in] url_recv, url_send
     **/
    void Broker::start(std::string url_recv, std::string url_send, xmlbus::XmlBus* xml, bool master)
    {
        // 1. 初始化pairs
        DataFusion::Get()->init_pairs(master);

        // 2. 启动helper
        g_helper_->start(url_recv, url_send, master);

        // 3. 启动辅助类
        DataFusion::Get()->start(id_, xml);
        DataHelper::Get()->start(id_);
    }

    /**
     *  @brief
     *     stop broker
     **/
    void Broker::stop()
    {
        if (g_helper_)
        {
            // 1. 停止服务线程
            g_helper_->stop();

            // 2. 销毁资源
            g_helper_->destroy();
        }

        DataFusion::Get()->stop();
        DataHelper::Get()->stop();
    }

    /**
     *  @brief
     *     enable to process data
     *  @param [in] type mean FrameDevType
     */
    void Broker::enable_proc(int type, bool fusion)
    {
        DataFusion::Get()->enable_proc(type, fusion);
    }
} // namespace broker
