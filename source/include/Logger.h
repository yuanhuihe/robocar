#pragma once

#include <mutex>
#include "spdlog/spdlog.h"

typedef enum _logIndex
{
    LI_Server = 0,
    LI_Client,
    LI_Imu,
    LI_Hi5,
    LI_Wii,
    LI_Motive,
    LI_Default,
    LI_Automatch,
    LI_MCTApp,
    LI_MCT,
    LI_Max,
}LogIndex;

class Logger
{
private:
    Logger(void);
    ~Logger(void);

private:
    char * GetRootPath(char * root_path);
    std::shared_ptr<spdlog::logger> m_logger[LI_Max]; // 日志文件
    std::shared_ptr<spdlog::logger> CreateLogger(LogIndex index, char* name);

private:
    static std::mutex mtx;

public:
    static Logger* Get();
    static std::shared_ptr<spdlog::logger> SpdLogger(LogIndex index);
    std::shared_ptr<spdlog::logger> GetLogger(LogIndex index);
};
