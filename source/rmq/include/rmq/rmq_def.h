#ifndef _RMQ_DEF_H_
#define _RMQ_DEF_H_

#include <string>
#include <memory>

namespace rmq
{
    /************************************************************************/
    /* Micro definitions                                                    */
    /************************************************************************/
    #define MAX_FRAME_BUFFER            1024

    #define BUFFER_128                  128
    #define BUFFER_256                  256
    #define BUFFER_512                  512
    #define BUFFER_1024                 1024

    /************************************************************************/
    /* Error code                                                           */
    /************************************************************************/
    #define ERMQ_OK                     0
    #define ERMQ_CREATE_IPC_FAILED      1
    #define ERMQ_DESTORY_IPC_FAILED     2
    #define ERMQ_TOO_SMALL_BUFFER       3
    #define ERMQ_RECVING_DATA_FAILED    4
    
    /************************************************************************/
    /* Data types                                                           */
    /************************************************************************/

    typedef struct
    {
        int64_t frm_index;
        int64_t time_code;
        int data_len;
    } rmq_frame_header_t;

    typedef struct
    {   rmq_frame_header_t header;
        char data[MAX_FRAME_BUFFER];
    } rmq_frame_t;


} // namespace rmq

#endif // !_RMQ_DEF_H_
