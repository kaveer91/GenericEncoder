#include "ReadFiles.h"
#include "Logger.h"
#include "TypeDefinitions.h"

#define TRACE_CLASS Logger::TRACE_CLASS_READFILES

std::string ReadFiles::GetFileExtension(const std::string& fileName)
{
	std::string fileExtension;
	if(!fileName.empty())
    {
        auto positionOfDot = fileName.find_last_of('.');
	    if(std::string::npos != positionOfDot)
        {
            fileExtension = fileName.substr(positionOfDot);
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower);
        }
	    else
        {
            LOG(Logger::LOG_LEVEL_ERROR, "Invalid file name. Not able to find extension");
        }
    }
	return fileExtension;
}

tBool ReadFiles::IsFileExtensionMatching(const std::string& fileName, Extension extensionToRead)
{
    tBool isMatching = false;
	std::string fileExtension = GetFileExtension(fileName);
    if(!fileExtension.empty())
    {
	    if(fileExtension == mapToFileExtension.find(extensionToRead)->second)
		{
			isMatching = true;
		}
		else
		{
			std::string errorMessage = std::string("File extension not matching for file : ") + fileName;
			LOG(Logger::LOG_LEVEL_DEBUG, errorMessage);
		}
    }	
	return isMatching;
}