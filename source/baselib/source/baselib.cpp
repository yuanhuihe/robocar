
#include <iostream>
#include <fstream>

//#include <ProjectRobocar/ProjectRobocar-version.h>

#include <baselib/baselib.h>
#include "spdlog/spdlog.h"


namespace baselib
{


void printInfo()
{
    std::string dataPath = "data";

    // Library name
    std::cout << "Library template::baselib" << std::endl;
    std::cout << "========================================" << std::endl;

    // Library version
    //std::cout << "Version: " << PROJECTROBOCAR_VERSION << std::endl;
    std::cout << std::endl;

    // Library type (static or dynamic)
    #ifdef BASELIB_STATIC_DEFINE
        std::cout << "Library type: STATIC" << std::endl;
    #else
        std::cout << "Library type: SHARED" << std::endl;
    #endif
    spdlog::set_async_mode(8192);
    auto file_logger = spdlog::rotating_logger_mt("file_logger", "demo", 1024 * 1024 * 5, 3);
    // Under VisualStudio, this must be called before main finishes to workaround a known VS issue
    spdlog::drop_all();
    file_logger->info("this is log info from lib");

}


} // namespace baselib
