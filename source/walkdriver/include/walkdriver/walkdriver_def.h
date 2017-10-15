
#pragma once


namespace WalkDriver
{
    // Execute error types
#define EET_OK                  0   // û�д���
#define EET_UnknownAction           1   // δ֪��������
#define EET_ActionNotSupport        2   // ָ���Ķ�����֧��

    // ��������
    enum ChassisType
    {
        CT_Unknown = 0,
        CT_MotorSystem,
        CT_FootWalkSystem,
    };

    // ִ�л�������
    enum ExecutiveDeviceType
    {
        EDT_Unknown = 0,
        EDT_DC_Motor,
        EDT_Stepper_Motor,
        EDT_Steering_Gear,
    };

    // �ƶ�����
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

    // �ƶ��ٶ�
    enum MoveSpeed
    {
        SL_Stop,
        SL_Slow,
        SL_Normal,
        SL_Fast,
    };






} // namespace WalkDriver
