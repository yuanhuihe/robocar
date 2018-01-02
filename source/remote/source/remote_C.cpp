#include <remote/remote_C.h>
#include <remote/remote.h>

namespace Remote
{
    REMOTE_API Remote_ref remote_create()
    {
        return new remote();
    }

    REMOTE_API void remote_release(Remote_ref& r)
    {
        remote* p = static_cast<remote*>(r);
        if(p)
        {
            p->stop();
            delete p;
            p = nullptr;
        }
    }

    REMOTE_API void remote_start(Remote_ref r, bool master)
    {
        remote* p = static_cast<remote*>(r);
        if(p)
        {
            p->start(master);
        }
    }

    REMOTE_API void remote_stop(Remote_ref r)
    {
        remote* p = static_cast<remote*>(r);
        if(p)
        {
            p->stop();
        }
    }
} // namespace Remote
