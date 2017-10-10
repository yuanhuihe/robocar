
#pragma once


namespace WalkDriver
{
    enum WalkType
    {
        WT_Unknown = 0,
        WT_Straight,
        WT_Normal,
        WT_Fast,
    };

    enum SpeedLevel
    {
        SL_Unknown = 0,
        SL_Slow,
        SL_Normal,
        SL_Fast,
    };


/**
*  @brief
*    Implement walk commands to driving wheels
*/
class WALKDRIVER_API Fibonacci
{
public:
    /**
    *  @brief
    *    Constructor
    */
    Fibonacci();

    /**
    *  @brief
    *    Destructor
    */
    virtual ~Fibonacci();

    /**
    *  @brief
    *    Calculate fibonacci number
    *
    *  @param[in] i
    *    Index
    *
    *  @return
    *    Value of the i'th fibonacci number
    */
    unsigned int operator()(unsigned int i);
};


} // namespace fiblib
