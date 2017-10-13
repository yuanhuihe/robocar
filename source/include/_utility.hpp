#pragma once

#include <string>
#include <time.h>
#include <experimental/filesystem>
#include <filesystem>
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
#else
#include <unistd.h>
#endif /* WIN32 */  

#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>


#define PATH_MAX 255

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
    char dest[PATH_MAX];
    memset(dest, 0, sizeof(dest)); // readlink does not null terminate!
#if WIN32
    GetModuleFileNameA(NULL, dest, PATH_MAX);
    int i = strlen(dest) - 1;
    while (dest[i] != '\\' && i >= 0)
    {
        dest[i] = 0;
        i--;
    }
#else
    struct stat info;
    pid_t pid = getpid();
    sprintf(path, "/proc/%d/exe", pid);
    if (readlink(path, dest, PATH_MAX) == -1)
        perror("readlink");
    else {
        printf("%s\n", dest);
    }
#endif

    return std::string(dest);
}