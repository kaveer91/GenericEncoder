#ifndef READ_FILES_H
#define READ_FILES_H

#include <algorithm>
#include <string>
#include "IReadFiles.h"

class ReadFiles : public IReadFiles
{
public:
	std::vector<std::string> Read(const std::string&, Extension) = 0;
	
protected:

    std::string GetFileExtension(const std::string& fileName);
	
    tBool IsFileExtensionMatching(const std::string& fileName, Extension extensionToRead);
};

#endif