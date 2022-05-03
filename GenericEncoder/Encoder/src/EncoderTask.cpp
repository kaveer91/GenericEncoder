#include "EncoderTask.h"
#include "Logger.h"
#include <exception>

#define TRACE_CLASS Logger::TRACE_CLASS_ENCODERTASK

EncoderTask::EncoderTask(IEncoder* iEncoder, const std::string& inputFileName, const std::string& outputFileName):
iEncoder(iEncoder), inputFileName(inputFileName), outputFileName(outputFileName)
{
	
}

void EncoderTask::Execute()
{
	try 
	{
	    iEncoder->Encode(inputFileName, outputFileName);
	}
	catch(const std::exception& xception)
	{
		LOG(Logger::LOG_LEVEL_FATAL, std::string("Exception: ") + xception.what() + ": caught while encoding file " +inputFileName);
	}
}
