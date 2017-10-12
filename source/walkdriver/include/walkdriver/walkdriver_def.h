
#pragma once


namespace WalkDriver
{
    // Execute error types
#define EET_OK                  0   // 没有错误
#define EET_UnknownAction           1   // 未知动作类型
#define EET_ActionNotSupport        2   // 指定的动作不支持

    // 底盘类型
    enum ChassisType
    {
        CT_Unknown = 0,
        CT_MotorSystem,
        CT_FootWalkSystem,
    };

    // 执行机构类型
    enum ExecutiveDeviceType
    {
        EDT_Unknown = 0,
        EDT_DC_Motor,
        EDT_Stepper_Motor,
        EDT_Steering_Gear,
    };

    // 移动类型
    enum MoveType
    {
        MT_Unknown = 0,
        MT_MoveForward,
        MT_MoveBackward,
        MT_Leftward,
        MT_Rightward,
        MT_BackLeft,
        MT_BackRigh,
    };

    // 移动速度
    enum MoveSpeed
    {
        SL_Stop,
        SL_Slow,
        SL_Normal,
        SL_Fast,
    };






} // namespace fiblib
