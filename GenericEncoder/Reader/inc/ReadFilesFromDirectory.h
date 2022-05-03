#ifndef READ_FILES_FROM_DIRECTORY_H
#define READ_FILES_FROM_DIRECTORY_H

#include <dirent.h>

#include "ReadFiles.h"


class ReadFilesFromDirectory : public ReadFiles
{
public:
    ReadFilesFromDirectory();
    
    std::vector<std::string> Read(const std::string& absolutePath, DIR* dir, Extension extensionToRead);

    std::vector<std::string> Read(const std::string& absolutePath, Extension extensionToRead);
};

#endif