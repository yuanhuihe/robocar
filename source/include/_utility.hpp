#pragma once

#include <string>
#include <time.h>
#include <experimental/filesystem>
#include <filesystem>
#include <iostream>
#include <fstream>

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
    std::error_code errorCode;
    bool error = false;
    std::experimental::filesystem::path myDirectory = path;
    if (std::experimental::filesystem::path::is_directory(myDirectory, errorCode))
    {
        if (std::experimental::filesystem::path::exists(myDirectory, errorCode))
        {
            // Process existing directory.
        }
        else
        {
            error = true;
        }
    }
    else
    {
        error = true;
    }

    if (error)
    {
        std::cout << errorCode.message() << std::endl;
        return false;
    }

    return true;
}


bool is_file_exit(char* file)
{
    std::ifstream _file(file);
    return _file.good();
}
