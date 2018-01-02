#pragma once

#include <stdint.h>
#include <time.h>

#ifdef WIN32
#include <Windows.h>   // LARGE_INTEGER, QueryPerformanceFrequency
#else
#include <sys/time.h>
#endif

/*
* 此模块获取1970到现在的时间，精度为us
* 平台： windows， unix， mac
*/

class HighPerfTimer
{
#ifdef WIN32
    LARGE_INTEGER __cpuFreq;
    LARGE_INTEGER StartingTime, EndingTime, ElapsedTime;
#else
    struct timeval StartingTime, EndingTime, ElapsedTime;
#endif // WIN32

    // 记录调用此函数时到1970年的微秒数
    uint64_t _1970usec;

public:
    HighPerfTimer(void);
    ~HighPerfTimer(void);

    // sleep, sleep_us:微秒数
    void Sleep(double usecond, bool exactly = false);

    // sleep mix, sleep_us:微秒数, percent: 低精度sleep占比
    void SleepMix(double usecond, int percent = 50);

    // 返回从1970年到调用此函数时的微秒数
    uint64_t GetTime();

private:
    bool SleepNano(double usecond);
    bool SleepHigh(double usecond);
};

