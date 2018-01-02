#include "HighPerfTimer.h"
#include <chrono>

HighPerfTimer::HighPerfTimer(void)
{
    // 获取从1970年1月1日0时到此时的微秒数
    std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
    // 记录调用此函数时到1970年的微秒数
    _1970usec = us.count();

#ifdef WIN32
    QueryPerformanceFrequency(&__cpuFreq);
    QueryPerformanceCounter(&StartingTime);
#else
    gettimeofday(&StartingTime, NULL);
#endif
}


HighPerfTimer::~HighPerfTimer(void)
{
}

void HighPerfTimer::Sleep(double usecond, bool exactly)
{
    if (exactly)
    {
        SleepHigh(usecond);
    }
    else
    {
        SleepNano(usecond);
    }
}

void HighPerfTimer::SleepMix(double usecond, int percent)
{
    if (usecond <= 0)
    {
        return;
    }

    uint64_t t1 = GetTime();
    double time = usecond * percent / 100;
    SleepNano(time);
    uint64_t t2 = GetTime();
    time = usecond - (t2 - t1);
    SleepHigh(time);
}

uint64_t HighPerfTimer::GetTime()
{
#ifdef WIN32
    QueryPerformanceCounter(&EndingTime);
    ElapsedTime.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    // 为了避免损失精度，先转换成微秒再除以CPU的频率
    ElapsedTime.QuadPart *= 1000000;    // 微秒
    ElapsedTime.QuadPart /= __cpuFreq.QuadPart;
    return _1970usec + ElapsedTime.QuadPart;
#else
    gettimeofday(&EndingTime, NULL);
    ElapsedTime.tv_sec = EndingTime.tv_sec - StartingTime.tv_sec;
    ElapsedTime.tv_usec = EndingTime.tv_usec - StartingTime.tv_usec;
    return ElapsedTime.tv_sec * 1000000 + ElapsedTime.tv_usec;
#endif
}

/* Windows sleep in 100ns units
* 经测试，精度在1ms以内
*/
bool HighPerfTimer::SleepNano(double usecond)
{
    if (usecond <= 0)
    {
        return false;
    }

#ifdef WIN32
    LONGLONG ns = usecond * 10.0f;
    /* Declarations */
    HANDLE timer;   /* Timer handle */
    LARGE_INTEGER li;   /* Time defintion */
                        /* Create timer */
    if (!(timer = CreateWaitableTimer(NULL, TRUE, NULL)))
        return false;
    /* Set timer properties */
    li.QuadPart = -ns;
    if (!SetWaitableTimer(timer, &li, 0, NULL, NULL, FALSE)) {
        CloseHandle(timer);
        return false;
    }
    /* Start & wait for timer */
    WaitForSingleObject(timer, INFINITE);
    /* Clean resources */
    CloseHandle(timer);
#else
    // TBD
#endif
    /* Slept without problems */
    return true;
}

/*
* 经测试，精度基本上为1us,很少情况下可以到10~20us，
*/
bool HighPerfTimer::SleepHigh(double usecond)
{
    if (usecond <= 0)
    {
        return false;
    }

#ifdef WIN32
    LARGE_INTEGER freq;                     // CUP频率
    LARGE_INTEGER count_base;               // 开始计数值
    LARGE_INTEGER count_curr;               // 当前技术值
    double passed_time;                     // 从0开始, 过来多长时间
    QueryPerformanceFrequency(&freq);       // 获得时钟频率
    QueryPerformanceCounter(&count_base);   // 获取开始寄存器计数值
    // 计时等待
    do
    {
        QueryPerformanceCounter(&count_curr);
        passed_time = ((count_curr.QuadPart - count_base.QuadPart) * 1000000) / freq.QuadPart;
    } while (passed_time < usecond);
#else
    struct timeval tmpStartingTime, tmpEndingTime;
    double currEslipsedTime;
    gettimeofday(&tmpStartingTime, NULL);
    do
    {
        gettimeofday(&tmpEndingTime, NULL);
        currEslipsedTime = (tmpEndingTime.tv_sec - tmpStartingTime.tv_sec) * 1000000 + (tmpEndingTime.tv_usec - tmpStartingTime.tv_usec);
    } while (currEslipsedTime < usecond);
#endif

    return true;
}
