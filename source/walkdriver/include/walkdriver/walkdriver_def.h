
#pragma once


namespace WalkDriver
{
    // Execute error types
#define EET_OK                      0   // No error
#define EET_UnknownAction           1   // Unknown moving command
#define EET_ActionNotSupport        2   // Not supported moving command

    // Chassis type
    enum ChassisType
    {
        CT_Unknown = 0,
        CT_MotorSystem,                 // 'MotorSystem.xml' config will be loaded at start
        CT_FootWalkSystem,              // 'FootWalkSystem.xml' config will be loaded at start
        CT_CaterpillarSystem,           // 'CaterpillarSystem.xml' config will be loaded at start
    };
    
    // Executive device type
    enum ExecutiveDeviceType
    {
        EDT_Unknown = 0,
        EDT_DC_Motor,
        EDT_Stepper_Motor,
        EDT_Steering_Gear,
    };
    
    // Where is the executive device set on
    enum ExecutiveDevicePartType
    {
        EDPT_Unknown = 0,
        EDPT_Head,
        EDPT_LeftShoulder,
        EDPT_RightShoulder,
        EDPT_LeftUpperArm,
        EDPT_RightUpperArm,
        EDPT_LeftForearm,
        EDPT_RightForearm,
        EDPT_LeftHand,
        EDPT_RightHand,
        EDPT_Hip,
        EDPT_LeftUpperLeg,
        EDPT_RightUpperLeg,
        EDPT_LeftLeg,
        EDPT_RightLeg,
        EDPT_LeftFoot,
        EDPT_RightFoot,
        //===================
        EDPT_LeftFrontWheel,
        EDPT_RightFrontWheel,
        EDPT_LeftBackWheel,
        EDPT_RightBackWheel,
    };

    // Moving type
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

    // Moving speed
    enum MoveSpeed
    {
        SL_Stop,
        SL_Slow,
        SL_Normal,
        SL_Fast,
    };






} // namespace WalkDriver
