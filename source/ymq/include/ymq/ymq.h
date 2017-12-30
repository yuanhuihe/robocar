/*
 * @brief
 * ymq proxy/hub
 *
 * @author Yuanhui He
 * @email  hyh618@gmail.com
 * @date 2017.12.30
*/

#ifndef YMQ_H_
#define YMQ_H_

#include <ymq_api.h>
#include <ymq/ymq_def.h>

#ifdef __cplusplus
extern "C" {
#endif
namespace ymq
{
    typedef void* ymq_proxy;
    typedef void* ymq_sock;

    /**************************** proxy/hub **********************************/
    /* @brief
    *   Create a proxy.
    */
    YMQ_API ymq_proxy ymq_new_proxy(int poll_port, int push_port);

    /* @brief
    *   Destory proxy.
    */
    YMQ_API ymq_sock ymq_proxy_destory(ymq_proxy& sock);
    /**************************** proxy/hub **********************************/


    /**************************** ymq socket **********************************/

    /* @brief
    *   Create a ymq socket.
    */
    YMQ_API ymq_sock ymq_new_sock(char* url);

    /* @brief
    *   Receive data on socket.
    */
    YMQ_API ymq_sock ymq_sock_recv(char* buff, int buff_len);

    /* @brief
    *   Send data by socket.
    */
    YMQ_API ymq_sock ymq_sock_send(char* data, int data_len);

    /* @brief
    *   Destory socket.
    */
    YMQ_API ymq_sock ymq_sock_destory(ymq_sock& sock);
    /**************************** ymq socket **********************************/


} // namespace ymq

#ifdef __cplusplus
}
#endif

#endif // !YMQ_H_
