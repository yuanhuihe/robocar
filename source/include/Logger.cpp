#include "Logger.h"
#ifdef MSVC
#include <corecrt_io.h>
#endif
#include <direct.h>
#include <commdlg.h>   // for GetSaveFileName
#include <shlobj.h>    // for SHGetFolderPath
// #include "spdlog/spdlog.h"

#define LOGGER_FOLDER   "logs\\"

std::mutex Logger::mtx;


Logger::Logger(void)
{
}

Logger::~Logger(void)
{
}

char* Logger::GetRootPath(char* root_path)
{
    char full_path[MAX_PATH] = { 0 };
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_COMMON_APPDATA, NULL, 0, full_path)))
    {
        sprintf(root_path, "%s\\%s", full_path, "Noitom\\");
        if (0 != _access(root_path, 0x00))
        {
            ::mkdir(root_path);
        }
    }
    return root_path;
}

std::shared_ptr<spdlog::logger> Logger::CreateLogger(LogIndex index, char* name)
{
    if (!m_logger[index])
    {
        char root_path[MAX_PATH] = { 0 };
        GetRootPath(root_path);

        char log_folder[MAX_PATH] = { 0 };
        sprintf(log_folder, "%s%s", root_path, LOGGER_FOLDER);

        char log_path[MAX_PATH] = { 0 };
        sprintf(log_path, "%s%s", log_folder, name);

        if (0 != _access(log_folder, 0x00))
        {
            ::mkdir(log_folder);
        }

        // 设置异步
        spdlog::set_async_mode(8192);
        m_logger[index] = spdlog::rotating_logger_mt(name, log_path, 1024 * 1024 * 5, 50);
        m_logger[index]->set_level(spdlog::level::debug);
        m_logger[index]->flush_on(spdlog::level::debug);
    }

    return m_logger[index];
}

Logger* Logger::Get()
{
    mtx.lock();
    static Logger s_logger;
    mtx.unlock();
    return &s_logger;
}

std::shared_ptr<spdlog::logger> Logger::SpdLogger(LogIndex index)
{
    return Logger::Get()->GetLogger(index);
}

std::shared_ptr<spdlog::logger> Logger::GetLogger(LogIndex index)
{
    switch (index)
    {
    case LI_Server:
        return CreateLogger(index, "server");
    case LI_Client:
        return CreateLogger(index, "client");
    case LI_Imu:
        return CreateLogger(index, "imu");
    case LI_Hi5:
        return CreateLogger(index, "hi5");
    case LI_Wii:
        return CreateLogger(index, "wii");
    case LI_Motive:
        return CreateLogger(index, "IPCR");
    case LI_MCTApp:
        return CreateLogger(index, "MCTApp");
    case LI_MCT:
        return CreateLogger(index, "MSG");
    }

    return CreateLogger(LI_Default, "default");
}
