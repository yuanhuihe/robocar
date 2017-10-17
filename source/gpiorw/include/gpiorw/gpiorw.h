/**
* @brief
*   GPIO controlling interface.
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#pragma once

#include <gpiorw/gpiorw_api.h>
#include <gpiorw/gpiorw_def.h>

namespace GPIORW
{
    /**
    *  @brief
    *    GPIO library init.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    GPIORW_API void GPIOLibInit(GPIOFunctionType type);

    /**
    *  @brief
    *    GPIO library release.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    GPIORW_API void GPIOLibRelease();

    /**
    *  @brief
    *    GPIO read.
    *
    *  @param[in] pin
    *   Pin will be write.
    *
    *  @return
    *    -1 means error occured. Otherwise the retured value is readed from gpio.
    */
    GPIORW_API int GPIORead(int pin);

    /**
    *  @brief
    *    GPIO write.
    *
    *  @param[in] pin
    *   Pin will be write.
    *
    *  @return
    *    -1 means error occured, 0 means successful.
    */
    GPIORW_API int GPIOWrite(int pin, int value);


} // namespace GPIORW
