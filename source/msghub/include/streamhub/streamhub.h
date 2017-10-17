/*
 * @brief
 * 本API只负责字节流传输
 *
 * @author 何元会
 * @date 2017.9.27
*/

#ifndef STREAMHUB_H_
#define STREAMHUB_H_

#include <streamhub_api.h>
#include <streamhub/streamhub_def.h>

#ifdef __cplusplus
extern "C" {
#endif
namespace StreamHub
{
    /* @brief
    *   设置用于接收数据的回调函数
    */
    STREAMHUB_API void setStreamDataReceivedCallback(void* userData, StreamDataReceivedCallback handle);

    /* @brief
    *   启动进程间通讯服务
    * @param [in] groupTag, 分组标识
    * @param [in] asHost, 如果是服务端调用则传入true，否则为false
    * @return
    *   成功返回0，否则返回错误码
    */
    STREAMHUB_API int start(char* groupTag, bool asHost, int& errn);

    /* @brief
    *   停止进程间通讯服务
    */
    STREAMHUB_API void stop(int& errn);

    
    STREAMHUB_API int bRunning();

    /* @brief
    *   发送IPC数据
    * @param
    *   - [in]data_stream, 需要发送的数据块
    *   - [in]stream_size, 需要发送的字节数
    *   - [in,out]errn, error number, successful with 0 outputed, other wise error occured
    * @return
    *   返回数据长度，单位：bytes
    */
    STREAMHUB_API int send(unsigned char* data, int len, int& errn);



} // namespace StreamHub

#ifdef __cplusplus
}
#endif

#endif // !STREAMHUB_H_
