#include "EncoderTask.h"

EncoderTask::EncoderTask(IEncoder* iEncoder, const std::string& inputFileName, const std::string& outputFileName):
iEncoder(iEncoder), inputFileName(inputFileName), outputFileName(outputFileName)
{
	
}

void EncoderTask::Execute()
{
	iEncoder->Encode(inputFileName, outputFileName);
}