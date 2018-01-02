#ifndef _REMOTE_CAPI_H_
#define _REMOTE_CAPI_H_

#include <remote/remote_api.h>
#include <remote/remote_def.h>

namespace Remote
{
#ifdef __cplusplus
extern "C" {
#endif

    /**
     *  @brief
     *     A remote instance reference.
     **/
    typedef void* Remote_ref;

    /**
     *  @brief
     *     Create a remote instance.
     *  @return
     *     Return an instance of remote, if failed, return null.
     **/
    REMOTE_API Remote_ref remote_create();

    /**
     *  @brief
     *     Release a remote instance.
     *  @return
     *     Return an instance of remote, if failed, return null.
     **/
    REMOTE_API void remote_release(Remote_ref& remote);

    /**
     *  @brief
     *     start remote
     *  @param [in] master, wether running as server or client
     **/
    REMOTE_API void remote_start(Remote_ref remote, bool master);

    /**
     *  @brief
     *     stop remote
     **/
    REMOTE_API void remote_stop(Remote_ref remote);
    

#ifdef __cplusplus
}
#endif
} // namespace Remote

#endif