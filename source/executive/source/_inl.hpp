/**
* @brief
*   Internel definitions file
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#ifndef _INL_HPP_
#define _INL_HPP_

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



#endif //!_INL_HPP_