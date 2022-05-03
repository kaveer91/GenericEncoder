#ifndef IREAD_FILES_H
#define IREAD_FILES_H

#include<vector>

#include "TypeDefinitions.h"

class IReadFiles
{
public:
    virtual std::vector<std::string> Read(const std::string&, Extension) = 0;
    
protected:
    virtual std::string GetFileExtension(const std::string& fileName) = 0;

    virtual tBool IsFileExtensionMatching(const std::string& fileName, Extension extensionToRead) = 0;
};

#endif