#ifndef _STREAMHUB_DEF_H_
#define _STREAMHUB_DEF_H_

#include <string>
#include <memory>

namespace StreamHub
{
    /************************************************************************/
    /* 数据定义                                                             */
    /************************************************************************/
    #define MAX_FRAME_BUFFER            1024

    #define BUFFER_128                  128
    #define BUFFER_256                  256
    #define BUFFER_512                  512
    #define BUFFER_1024                 1024

    /************************************************************************/
    /* 错误定义                                                             */
    /************************************************************************/
    #define EIPC_CREATE_IPC_FAILED      1
    #define EIPC_DESTORY_IPC_FAILED     2
    #define EIPC_TOO_SMALL_BUFFER       3
    #define EIPC_RECVING_DATA_FAILED    4
    
    /************************************************************************/
    /* 数据类型定义                                                          */
    /************************************************************************/

    /* @brief
    *   数据流回调
    */
    typedef void(*StreamDataReceivedCallback)(void* userData, unsigned char* data, int len);
    

    /* @brief
    *   指令数据回调函数
    */
    typedef void(*IPCCommandReceivedCallback)(void* userData, unsigned char* data, int len);

} // namespace StreamHub

#endif // !_STREAMHUB_DEF_H_
