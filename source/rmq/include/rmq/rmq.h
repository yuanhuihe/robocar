/*
 * @brief
 * Remote message queue proxy/hub
 *
 * @author Yuanhui He
 * @email  hyh618@gmail.com
 * @date 2017.12.30
*/

#ifndef RMQ_H_
#define RMQ_H_

#include <rmq_api.h>
#include <rmq/rmq_def.h>

#ifdef __cplusplus
extern "C" {
#endif
namespace rmq
{
    typedef void* rmq_proxy_t;
    typedef void* rmq_sock_t;

    /**************************** proxy/hub **********************************/
    /* @brief
    *   Create a proxy.
    */
    RMQ_API rmq_proxy_t rmq_new_proxy(char* url_poll, char* url_push);

    /* @brief
    *   Destory proxy.
    */
    RMQ_API void rmq_proxy_destory(rmq_proxy_t& sock);
    /**************************** proxy/hub **********************************/


    /**************************** rmq socket **********************************/

    /* @brief
    *   Create a rmq socket.
    */
    RMQ_API rmq_sock_t rmq_new_sock(const char* url);

    /* @brief
    *   Receive data on socket.
    */
    RMQ_API int rmq_sock_recv(rmq_sock_t sock, char* buff, int buff_len);

    /* @brief
    *   Receive data on socket.
    */
    RMQ_API int rmq_sock_recv_ref(rmq_sock_t sock, char** data, int* len);

    /* @brief
    *   Send data by socket.
    */
    RMQ_API int rmq_sock_send(rmq_sock_t s, char* data, int len);

    /* @brief
    *   Set receive timeout.
    */
    RMQ_API int rmq_set_sock_recv_timeout(rmq_sock_t s, int timeout);

    /* @brief
    *   Set send timeout.
    */
    RMQ_API int rmq_set_sock_send_timeout(rmq_sock_t s, int timeout);

    /* @brief
    *   Destory socket.
    */
    RMQ_API void rmq_sock_destory(rmq_sock_t& sock);
    /**************************** rmq socket **********************************/


} // namespace rmq

#ifdef __cplusplus
}
#endif

#endif // !RMQ_H_
