
#pragma once


namespace WalkDriver
{
    enum ExecutiveDeviceType
    {
        EDT_Unknown = 0,
        EDT_DC_Motor,
        EDT_Stepper_Motor,
        EDT_Steering_Gear,
    };

    enum WalkType
    {
        WT_Unknown = 0,
        WT_Run,
        WT_Stop,
    };

    enum SpeedLevel
    {
        SL_Unknown = 0,
        SL_Slow,
        SL_Normal,
        SL_Fast,
    };
    
} // namespace fiblib
