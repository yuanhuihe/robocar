#ifndef DATAFRAMEPOOL_H_
#define DATAFRAMEPOOL_H_

#include <mutex>
#include "MemoryPool.h"

#define DATA_OF_FRAME_LEN  4096

template<class T>
class DataFramePool
{
private:
    DataFramePool()
    {
    }

    ~DataFramePool()
    {
    }

public:
    #define SafetyNew(dataLen) _SafetyNew(dataLen, __func__, __FILE__, __LINE__)
    static T* _SafetyNew(int dataLen, const char* fun, const char* file, int line)
    {
        std::lock_guard<std::mutex> l(_inst->mtx);

        if (dataLen > DATA_OF_FRAME_LEN)
        {
            printf("%s() _%s:%d: received a big data block, len=%d throw away.\n", fun, file, line, dataLen);
            return nullptr;
        }

        return _inst->frame_pool.newElement();
    }

    static void ReleaseFrame(T*& frame)
    {
        if (frame == nullptr) return;

        std::lock_guard<std::mutex> l(_inst->mtx);
        _inst->frame_pool.deleteElement(frame);
        frame = nullptr;
    }

    static void ReleasePool()
    {
        if (_inst) delete _inst;
        _inst = nullptr;
    }

private:
    static DataFramePool<T>* _inst;
    MemoryPool<T, 4096 * 4096 * 2>  frame_pool;
    std::mutex                      mtx;

private:

};

template<class T>
DataFramePool<T>* DataFramePool<T>::_inst = new DataFramePool<T>();

#endif //!DATAFRAMEPOOL_H_