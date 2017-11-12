#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <atomic>
#include <functional>
#include <sys/types.h>
#if WIN32
#include <io.h>  
#include <process.h>  
#else
#include <unistd.h>
#endif /* _UNISTD_H */  

#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>


//// 底盘类型列表
//std::tuple<ChassisType, std::string> ChassisTypeMap[] = {
//    { CT_MotorSystem,"MotorSystem.xml" },
//    { CT_FootWalkSystem,"FootWalkSystem.xml" }
//};

struct sActionConfig
{

};