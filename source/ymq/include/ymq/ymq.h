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
    typedef void* ymq_proxy_t;
    typedef void* ymq_sock_t;

    /**************************** proxy/hub **********************************/
    /* @brief
    *   Create a proxy.
    */
    YMQ_API ymq_proxy_t ymq_new_proxy(char* url_poll, char* url_push);

    /* @brief
    *   Destory proxy.
    */
    YMQ_API void ymq_proxy_destory(ymq_proxy_t& sock);
    /**************************** proxy/hub **********************************/


    /**************************** ymq socket **********************************/

    /* @brief
    *   Create a ymq socket.
    */
    YMQ_API ymq_sock_t ymq_new_sock(char* url);

    /* @brief
    *   Receive data on socket.
    */
    YMQ_API int ymq_sock_recv(ymq_sock_t s, char* buff, int buff_len);

    /* @brief
    *   Send data by socket.
    */
    YMQ_API int ymq_sock_send(ymq_sock_t s, char* data, int data_len);

    /* @brief
    *   Set receive timeout.
    */
    YMQ_API int ymq_set_sock_recv_timeout(ymq_sock_t s, int timeout);

    /* @brief
    *   Set send timeout.
    */
    YMQ_API int ymq_set_sock_send_timeout(ymq_sock_t s, int timeout);

    /* @brief
    *   Destory socket.
    */
    YMQ_API void ymq_sock_destory(ymq_sock_t& sock);
    /**************************** ymq socket **********************************/


} // namespace ymq

#ifdef __cplusplus
}
#endif

#endif // !YMQ_H_
