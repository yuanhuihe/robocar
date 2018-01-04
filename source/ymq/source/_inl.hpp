#ifndef _INL__HPP_
#define _INL__HPP_

#include <functional>           // std::bind
using namespace std::placeholders;

namespace ymq
{
#define MAX_EVENT_COUNT     5000
#define MAX_RECV_BUFF_SIZE  65535
#define LISTEN_BACKLOG      50

    typedef std::function<void(char*, int)> fn_received_data_handle;

} // namespace ymq
#endif //!_INL__HPP_