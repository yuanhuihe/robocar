#include "Utility.h"
#include <windows.h>

namespace Utility
{
    // 检查IP输入
    bool check_ip(char* ip, int len)
    {
        if (len > 15)
        {
            return false;
        }

        char cText[4][16];
        char cDelim = '.';
        memset(cText, 0x00, sizeof(cText));

        int iText = 0;
        int iTextPos = 0;
        // 1. 判断字段数
        for (int i = 0; i < len; i++)
        {
            // 忽略_T('.')
            if (cDelim == ip[i])
            {
                iText++;
                iTextPos = 0;
                continue;
            }

            // 判断字符为数字
            if ((ip[i] < '0') || (ip[i] > '9'))
            {
                return false;
            }

            // 判断分割符
            if (iText >= 4)
            {
                return false;
            }

            // 复制字符串
            cText[iText][iTextPos++] = ip[i];
            if (iTextPos > 3)
            {
                return false;
            }
        }

        // 2. 每个字段检查
        for (int i = 0; i < 4; i++)
        {
            if (0 == strlen(cText[i]))
            {
                return false;
            }

            // 255以内
            int num = atoi(cText[i]);
            if (num > 255)
            {
                return false;
            }
            else if (((num == 0) || (127 == num)) && (i < 1))
            {
                return false;
            }
        }

        return true;
    }
}

