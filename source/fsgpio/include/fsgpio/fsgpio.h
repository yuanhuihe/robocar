/**
* @brief
*   GPIO controlling by file system.
*
* @author
*   Yuanhui HE
*
* @Date
*   2017.10.12
*/
#pragma once

#include <fsgpio/fsgpio_api.h>
#include <fsgpio/fsgpio_def.h>

namespace FSGPIO
{
    /**
    *  @brief
    *    GPIO library init.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    FSGPIO_API void GPIOLibInit();

    /**
    *  @brief
    *    GPIO library release.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    FSGPIO_API void GPIOLibRelease();

    /**
    *  @brief
    *    GPIO read.
    *
    *  @param[in] pin
    *   Pin will be write.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    FSGPIO_API int GPIORead(int pin);

    /**
    *  @brief
    *    GPIO write.
    *
    *  @param[in] pin
    *   Pin will be write.
    *
    *  @return
    *    0 means successful, -1 means error occured.
    */
    FSGPIO_API int GPIOWrite(int pin, int value);


} // namespace FSGPIO
