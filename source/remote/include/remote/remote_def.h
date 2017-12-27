#ifndef _REMOTE_DEF_H_
#define _REMOTE_DEF_H_

#include <stdint.h>

namespace Remote
{
#define MAX_DATA_LEN    4096    // max data len

    struct TransFrame
    {
        int frame_index;
        uint64_t time_stamp;
        int len;                // data length
        char data[MAX_DATA_LEN];
    };


} // namespace Remote

#endif //!_REMOTE_DEF_H_