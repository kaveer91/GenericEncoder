#include <string.h>
#include <algorithm>

#include "ReadFilesFromDirectory.h"
#include "Logger.h"
#include "TypeDefinitions.h"

#define TRACE_CLASS Logger::TRACE_CLASS_READFILES

ReadFilesFromDirectory::ReadFilesFromDirectory()
{
	
}

std::vector<std::string> ReadFilesFromDirectory::Read(const std::string& absolutePath, DIR* dir, Extension extensionToRead)
{
	std::vector<std::string> filesMatched;
	if(dir && !absolutePath.empty())
	{
		struct dirent *entry = nullptr;
		do
		{
			errno = 0;
		    entry = readdir(dir);
		    if(entry)
		    {
				std::string entryName = entry->d_name;
				if(!entryName.empty())
				{
					std::string entryAbsolutePath = absolutePath + "/" + entryName;
					
			        if(DT_REG == entry->d_type)
                    {
						LOG(Logger::LOG_LEVEL_DEBUG, std::string("Regular file found : ") + entryAbsolutePath);
				        if(IsFileExtensionMatching(entryName, extensionToRead))
					    {
						    filesMatched.push_back(entryAbsolutePath);
					    }
				    }
	    			else if(DT_DIR == entry->d_type)
		    		{
						if(std::string::npos == entryName.find(".") && std::string::npos == entryName.find(".."))
						{
			    		    LOG(Logger::LOG_LEVEL_DEBUG, std::string("directory entry found : ") + entryAbsolutePath);
						    std::vector<std::string> filesMatchedFromSubDirectory = Read(entryAbsolutePath, extensionToRead);
							for(auto iter: filesMatchedFromSubDirectory)
							{
								filesMatched.push_back(iter);
							}
						}
				    }
					else
					{
						LOG(Logger::LOG_LEVEL_DEBUG, std::string("File type not interested : ") + entryAbsolutePath);
					}
				}
                else
				{
					LOG(Logger::LOG_LEVEL_DEBUG, std::string("Entry name empty "));
				}					
			}
			else if(0 != errno)
			{
                std::string errorMessage = std::string("Directory Entry null") + strerror(errno);
			    LOG(Logger::LOG_LEVEL_ERROR, errorMessage);
			}
		}while((NULL != entry) || (NULL == entry && 0!= errno));
	}
    return filesMatched;
}

std::vector<std::string> ReadFilesFromDirectory::Read(const std::string& absolutePath, Extension extensionToRead)
{
	LOG(Logger::LOG_LEVEL_DEBUG, std::string("Reading from directory") + absolutePath);
    std::vector<std::string> listOfFiles;
	
    if(!absolutePath.empty())
    {
        DIR* dir = opendir(absolutePath.c_str());
	
        if(dir)
        {
            listOfFiles = Read(absolutePath, dir, extensionToRead);
			
			if(closedir(dir))
			{
				std::string errorMessage = std::string("Failed to close directory : ") + strerror(errno);
			    LOG(Logger::LOG_LEVEL_ERROR, errorMessage);
			}
        }
        else
        {
			std::string errorMessage = std::string("Failed to open directory : ") + strerror(errno);
			LOG(Logger::LOG_LEVEL_ERROR, errorMessage);
        }
    }
    else
    {	
        LOG(Logger::LOG_LEVEL_ERROR, "Directory path empty");
    }
	
	return listOfFiles;
}
