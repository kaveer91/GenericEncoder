#ifndef ENCODER_TASK_H
#define ENCODER_TASK_H

#include "ITask.h"
#include "IEncoder.h"

#include <string>
#include <memory>

class EncoderTask : public ITask
{
public:
    EncoderTask(IEncoder* iEncoder, const std::string& inputFileName, const std::string& outputFileName);
    void Execute();
private:
    IEncoder* iEncoder;
    std::string inputFileName;
	std::string outputFileName;
};

#endif