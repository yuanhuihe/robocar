#pragma once

namespace GPIORW
{
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#if defined(_MSC_VER)
#include <corecrt_io.h>         // for open/write/read
#include <BaseTsd.h>
    typedef SSIZE_T ssize_t;        // for ssize_t
#else
#include <unistd.h>
#endif

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

#define PIN_MAX_COUNT 64




}  // name space GPIORW