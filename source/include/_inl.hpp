#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <atomic>
#include <functional>

/************************************************************************/
/* 数据定义                                                             */
/************************************************************************/
#define INDEX_INVALID               -1
#define STR_DEV_MCT	                "MSG"   // 设备


#define send_channel                "6601"
#define recv_channel                "6602"

#define STR_LOCALHOST               "inprc://bstream_router"

#define STR_PORT_CMD                "6111"  // 命令通道
#define STR_PORT_DATA               "6112"  // 数据通道
#define STR_PORT_STAT               "6113"  // 状态通道

#define STR_FRAME_CMD               "CMD"   // 命令
#define STR_FRAME_DATA              "DATA"  // 数据
#define STR_FRAME_STAT              "STAT"  // 状态

#define FORMAT_SEND_DEALER          "ssb"   // char* + char* + byte*
#define FORMAT_SEND_PUB             "ssb"   // char* + char* + byte*

#define FORMAT_RECV_ROUTER          "sssb"  // char*(empty string) + char* + char* + byte*
#define FORMAT_RECV_PROXY           "sssb"  // char*(empty string) + char* + char* + byte*
#define FORMAT_RECV_SUB             "ssb"   // char* + char* + byte*

#define FORMAT_CMD_MERGE            "%s.%s"
#define FORMAT_CMD_SPLIT            "%[^.].%[^.]"

#define DELAY_PUB_1MS               1       // 1ms
#define DELAY_SUB_1S                1       // 1s
#define RECV_SLEEP_1MS              1       // 1ms
#define SEND_SLEEP_1MS              1       // 1ms
#define SLEEP_100MS                 100     // 100ms
#define WRITE_SLEEP_100MS           100     // 100ms

/************************************************************************/
/* Debug information                                                    */
/************************************************************************/
#define DEBUG_PRINT                 0
#if DEBUG_PRINT
#define DEBUGSTR(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUGSTR(fmt, ...)             // empty
#endif

/************************************************************************/
/* abstract factory                                                     */
/************************************************************************/
#pragma pack(push, 1)

template<unsigned char c0, unsigned char c1, unsigned char c2, unsigned char c3>
struct MakeFourCC
{
    static const unsigned int value = (c0 | c1 << 8 | c2 << 16 | c3 << 24);
};

typedef struct _byte_data
{
    uint8_t* data;
    int len;
}byte_data;


#pragma pack(pop)

#define SafeDelete(p)  if (p != nullptr) { delete p; p = nullptr; }
#define SafeDeletes(p) if (p != nullptr) { delete [] p; p = nullptr; }
#define SafeFree(p)  if (p != nullptr) { free(p); p = nullptr; }
#define SafeCloseThread(p1, p2) if (p1 != nullptr) { p2 = false; p1->join(); delete p1; p1 = nullptr; }
#define SafeCloseHandle(p) if (p != nullptr) { CloseHandle(p); p = nullptr; }
#define SafeCloseFile(p) if(p != NULL) { fclose(p); p = NULL;}

#define FLOAT_MIN_VAL 0.0f

/************************************************************************/
/* 测试传输通道                                                         */
/************************************************************************/
static const char* URL_DRV_PUB = "@tcp://localhost:9020";
static const char* URL_DRV_SUB = ">tcp://localhost:9020";

/************************************************************************/
/* 测试传输通道                                                         */
/************************************************************************/

/************************************************************************/
/* Agent                                                                */
/************************************************************************/
#define DRV_CMD_SET "set"
#define DRV_CMD_GET "get"
#define DRV_CMD_DATA "data"
//typedef void (*func_callback_notify)(int);


/************************************************************************/
/* callback                                                             */
/************************************************************************/
// clients to server by router.
typedef std::function<void(char*, char*, char*, int)> recv_callback_cmd;
typedef std::function<void(char*, char*, char*, int)> recv_callback_data;
typedef std::function<void(char*, char*, char*, int)> recv_callback_stat;

// server to clients by router.
typedef std::function<void(char*, char*, char*, int)> send_callback;
typedef std::function<void(char*, char*, char*, int)> send_callback_data;
typedef std::function<void(char*, char*, char*, int)> send_callback_stat;

// p2p callback
typedef std::function<void()> recv_callback;
typedef std::function<void(void*)> recv_callback_p2p;
typedef std::function<void(void*, char*)> recv_callback_vc;

// clients to ui.
typedef std::function<void(char*, int)> fn_notify_stat;

// 设备内部的回调
typedef std::function<void(char*, int)> inner_callback_cmd;
typedef std::function<void(char*, int)> inner_callback_data;
typedef std::function<void(void*)> inner_callback_data_ex;
typedef std::function<void()> inner_callback_stat;
typedef std::function<void(int)> inner_callback_stat_ex;
typedef std::function<void(char*, int)> inner_callback_stat_ex2;
typedef std::function<int(char*, int)> inner_send_callback;
typedef std::function<void(char*, int)> inner_recv_callback;


typedef std::function<void(int)> fu_callback_notify;
/************************************************************************/
/* callback                                                             */
/************************************************************************/


enum ConfigType {
    CT_DRV = 0,
    CT_CONFIG,
    CT_PROJECT,
	CT_SYN,
    CT_MAX
};
