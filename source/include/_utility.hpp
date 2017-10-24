#pragma once

#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <atomic>
#include <functional>
#include <sys/types.h>
#if WIN32 
#include <Winbase.h>            // GetModuleFileNameA
#include <io.h>  
#include <process.h>  
#define PATH_MAX 255
#else
#include <unistd.h>
#endif /* WIN32 */  

#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>



inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

/* @brief Generate uuid based on current time
*/
void generateUuid(char *guidStr)
{
    char *pGuidStr = guidStr;
    int i;
    
    /*Randomize based on time.*/
    srand(static_cast<unsigned int> (time(NULL)));

    /*Data1 - 8 characters.*/
    //*pGuidStr++ = '{';
    for (i = 0; i < 8; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data2 - 4 characters.*/
    *pGuidStr++ = '-';
    for (i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data3 - 4 characters.*/
    *pGuidStr++ = '-';
    for (i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data4 - 4 characters.*/
    *pGuidStr++ = '-';
    for (i = 0; i < 4; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    /*Data5 - 12 characters.*/
    *pGuidStr++ = '-';
    for (i = 0; i < 12; i++, pGuidStr++)
        ((*pGuidStr = (rand() % 16)) < 10) ? *pGuidStr += 48 : *pGuidStr += 55;

    //*pGuidStr++ = '}';
    *pGuidStr = '\0';
}

bool is_dir_exit(char* path)
{
    // TBD




    
    return false;
}


bool is_file_exit(char* file)
{
    std::ifstream _file(file);
    return _file.good();
}

std::string get_curr_dir()
{
    char path[PATH_MAX];
    memset(path, 0, sizeof(path));
#if WIN32
    GetModuleFileNameA(NULL, path, PATH_MAX);
    int i = strlen(path) - 1;
    while (path[i] != '\\' && i >= 0)
    {
        path[i] = 0;
        i--;
    }
#else
    if (!getcwd(path, PATH_MAX))
    {
        perror("getcwd");
    }
    else
    {
        strncat(path, "/", PATH_MAX);
    }
#endif

    return std::string(path);
}

std::wstring str2wstr(char* str)
{
    #if 0
    if (str == nullptr) return std::wstring();

    size_t len = strlen(str) + 1;
    size_t converted = 0;

    wchar_t *wstr = (wchar_t*)malloc(len * sizeof(wchar_t));
    mbstowcs_s(&converted, wstr, len, str, _TRUNCATE);
    std::wstring w(wstr);

    free(wstr);

    return w;
    #endif
    return std::wstring();
}

std::string wstr2str(wchar_t* wStr)
{
    if (wStr == nullptr) return "";

    std::wstring w(wStr);
    std::string str;
    str.assign(w.begin(), w.end());

    return str;
}