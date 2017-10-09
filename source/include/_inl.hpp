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
#define STR_DEV_MCT	                "MSG"   // Multi-Cmaera Tracing 设备


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


typedef struct _RigidbodyInfo
{
    unsigned int hash;
    int externalID;
    float data[10];
}RigidbodyInfo;

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
static const char* URL_MTV_PUB = "@tcp://localhost:9020";
static const char* URL_MTV_SUB = ">tcp://localhost:9020";

/************************************************************************/
/* 测试传输通道                                                         */
/************************************************************************/

/************************************************************************/
/* Agent                                                                */
/************************************************************************/
#define OP_AG_CMD_SET "set"
#define OP_AG_CMD_GET "get"
#define OP_AG_CMD_DATA "data"
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
#define SENSER_ID_MAX           128
#define RIGID_BODY_ID_MAX       0x400
#define RIGID_BODY_ID_MASK      0x3ff

#define MAXMARKENUM             10
#define FLMOTIVETMARKERNUM      10
#define OPTIONMARKERORDERNUM    10

enum AppWinType
{
    START_APP,
    STOP_APP
};

enum Devicetype
{
    DEV_NONE = -1,          // 无效
    DEV_HMD = 1000,         // 头显
    DEV_CONTROL = 2000,     // 控制器
    DEV_PROP = 3000,        // 道具
    DEV_HI5 = 4000,         // hi5
	DEV_HI5_LEFT = 4100,    // hi5
	DEV_HI5_RIGHT = 4200,   // hi5
    DEV_NEURON = 5000,      // neuron
};

enum ControllType
{
    CTR_NONE = -1,      // 无效
    CTR_WII = 1,        // Wii
    CTR_CHICKHANDLE = 2,// 小鸡手柄
    DEV_KEYBOARD = 3    // 键盘
};

// Alice通用设备
struct AliceDevice
{
    bool valid;             // [基本属性] 是否可用
    int dev_id;             // [基本属性] 设备索引
    int type;               // [基本属性] DeviceType
    std::string name;       // [基本属性] name

    bool use_rigid;         // [光学属性] 使用刚体
    int rigid_id;           // [光学属性] rigid id
    std::string rigid_name; // [光学属性] rigid name
    
    bool use_imu;           // [惯性属性] 使用imu
    int imu_id;             // [惯性属性]-1 无， 
    std::string imu_sn;     // [惯性属性] RigidBody data fusion with hmd IMU, this field filled with SN of HMD
    
    bool use_ctrl;          // [控制器属性] 使用控制器
    int ctrl_type;          // [控制器属性] 控制器类型
    int ctrl_id;            // [控制器属性] 控制器id
    std::string ctrl_sn;    // [控制器属性] 控制器sn
    
    AliceDevice()
    {
        valid = false;              // [基本属性] 是否可用
        dev_id = INDEX_INVALID;     // [基本属性] 设备索引
        type = DEV_NONE;            // [基本属性] DeviceType

        use_rigid = false;          // [光学属性] 使用刚体
        rigid_id = INDEX_INVALID;   // [光学属性] rigid id

        use_imu = false;            // [惯性属性] 使用imu
        imu_id = INDEX_INVALID;     // [惯性属性]-1 无， 

        use_ctrl = false;           // [控制器属性] 使用控制器
        ctrl_type = CTR_NONE;       // [控制器属性] 控制器类型
        ctrl_id = INDEX_INVALID;    // [控制器属性] 控制器id
    }
};

// Alice客户端
struct AliceClient
{
    std::string id;     // uuid
    std::string name;   // name
    std::string ip;     // ip
    int ClientCode;
    int OwnerType;
    int RuningApp;
    std::vector<int> dev_vec;
};

// Alice通用设备Shark
struct AliceShark : public AliceDevice
{
    int res_n;
};

struct StructMutex
{
    std::mutex nmutex;
};

struct xml_track_rigid_ui : public StructMutex
{
    std::string CalibrationName_val;
    std::string CalibrationName_type;

    std::string ExternalID_value;
    std::string ExternalID_type;

    std::string MarkerCount_value;
    std::string MarkerCount_type;

    std::vector < std::tuple <
        std::string, // 节点名称 name
        std::string, // type
        std::string, // z
        std::string, // y
        std::string // x
        >> Markers_vec;
    // Transforms - WiiMote_Adjustable - Position
    std::string model_type;
    std::tuple <
        std::string, // type
        std::string, // x
        std::string, // y
        std::string // z
    > Position_tup;

    // Transforms - WiiMote_Adjustable - <Rotation 
    std::tuple <
        std::string, // type
        std::string, // x
        std::string, // y
        std::string, // z
        std::string // w
    > Rotation_tup;

    // Transforms - WiiMote_Adjustable - Scale
    std::tuple <
        std::string, // type
        std::string, // x
        std::string, // y
        std::string // z
    > Scale_tup;

    std::vector<
        std::tuple <
        std::string, // 节点名称 name
        std::string, // type
        std::string, // x
        std::string, // y
        std::string  // z
        >
    > CustomMarkers_vec;

    std::vector<
        std::tuple <
        std::string, // 节点名称 name
        std::string, // type
        std::string  // value
        >
    > selectSideSum_vec;

    int rigid_id_n;
    int hide_n;
    int senser_id_n;
    int action_flg_n;
    int is_cal;
    int dev_id;
    void cp_xml_data(std::shared_ptr<xml_track_rigid_ui> p)
    {
        CalibrationName_val = p->CalibrationName_val;
        CalibrationName_type = p->CalibrationName_type;
        ExternalID_value = p->ExternalID_value;
        ExternalID_type = p->ExternalID_type;
        MarkerCount_value = p->MarkerCount_value;
        MarkerCount_type = p->MarkerCount_type;
        Markers_vec = p->Markers_vec;
        Position_tup = p->Position_tup;
        Rotation_tup = p->Rotation_tup;
        Scale_tup = p->Scale_tup;
        CustomMarkers_vec = p->CustomMarkers_vec;
        selectSideSum_vec = p->selectSideSum_vec;
    }
    xml_track_rigid_ui()
        : rigid_id_n(-1)
        , hide_n(-1)
        , senser_id_n(-1)
        , action_flg_n(-1)
        , is_cal(-1)
        , dev_id(-1)
    {

    }
};

enum ConfigType {
    CT_AGENT = 0,
    CT_CONFIG,
    CT_PROJECT,
	CT_SYN,
    CT_MAX
};
/************************************************************************/
/* XmlBus                                                               */
/************************************************************************/
/************************************************************************/
/* p2p通信                                                              */
/************************************************************************/
#define STR_GLOBAL              "GLOBAL"
#define P2P_PORT                15670

#define STR_P2P_MASTER          "ALICE-SERVER-"
#define STR_SERVER_READY        "ready-s"
#define STR_CLIENT_READY        "ready-c"

#define Peer_S_HeatBeat         "heartbeat-s"
#define Peer_S_DetailReq        "detailreq-s"
#define Peer_S_JoinGroup        "joingroup-s"
#define Peer_S_SyncNeed         "syncneed-s"
#define Peer_S_Config           "config-s"
#define Peer_S_SyncRep          "syncreq-s"
#define Peer_S_BTSyncNeed       "btsyncneed-s"

#define Peer_C_HeatBeat         "heartbeat-c"
#define Peer_C_DetailRep        "detailrep-c"
#define Peer_C_JoinConfirm      "joinconfirm-c"
#define Peer_C_SyncConfig       "syncconfig-c"
#define Peer_C_ConfigConfirm    "configconfirm-c"
#define Peer_C_SyncReq          "syncreq-c"
#define Peer_C_BTSynID          "btsyncid-c"

// p2p数据类型-server
enum FramePeerServer
{
    FPS_Unkown = 0,     // 未知消息类型
    FPS_HeartBeat,      // 心跳
    FPS_DetailReq,      // 详细信息
    FPS_JoinGroup,      // 加入新组
    FPS_SyncNeed,       // 需要同步
    FPS_Config,         // 配置数据
    FPS_SyncRep,        // 同步反馈
    FPS_BtSyncNeed,     // 需要BT同步
    FPS_Max,            // 最大消息类型
};

// p2p数据类型-client
enum FramePeerClient
{
    FPC_Unkown = 0,     // 未知消息类型
    FPC_HeartBeat,      // 心跳
    FPC_DetailRep,      // 详细信息
    FPC_JoinConfirm,    // 加入新组确认
    FPC_SyncConfig,     // 同步配置
    FPC_ConfigConfirm,  // 配置确认
    FPC_SyncReq,        // 同步请求
    FPC_BtSyncID,       // 客户端返回id和key
    FPC_Max,            // 最大消息类型
};

/************************************************************************/
/* p2p通信                                                              */
/************************************************************************/