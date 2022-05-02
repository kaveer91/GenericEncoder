
#include<memory>

#include "Logger.h"
#include "TypeDefinitions.h"
#include "ReadFilesFromDirectory.h"
#include "LameWavToMp3Encoder.h"

#define TRACE_CLASS Logger::TRACE_CLASS_MAIN

const tU16 inputArgumentCount = 2;

tS32 main(tS32 argumentCount, char* argument[])
{
	
	if(inputArgumentCount == argumentCount)
	{
        LOG(Logger::LOG_LEVEL_DEBUG, "valid number of arguments");
		 
		//1.Read files from directory
		std::string directoryName = argument[1];
		std::shared_ptr<IReadFiles> iReadFiles = std::make_shared<ReadFilesFromDirectory>();
		std::vector<std::string> listOfMatchedFiles = iReadFiles->Read(directoryName, EXT_WAV);
		
		//2.Encode the files read using 
		if(listOfMatchedFiles.size() > 0)
		{
			LOG(Logger::LOG_LEVEL_INFO, "Found " + std::to_string(listOfMatchedFiles.size())+" files for encoding");
		    std::shared_ptr<IEncoder> iEncoder = std::make_shared<LameWavToMp3Encoder>();	
		    iEncoder->Encode(listOfMatchedFiles);
		}
		else
		{
			LOG(Logger::LOG_LEVEL_INFO, "No valid files found for encoding");
		}
	}
	else
	{
		LOG(Logger::LOG_LEVEL_ERROR, "Invalid number of arguments");
		LOG(Logger::LOG_LEVEL_ERROR, "Usage : ./Encoder FolderName");
	}
	return 0;
}