#include "WavToMp3Encoder.h"
#include "TypeDefinitions.h"
#include "Logger.h"
#include "ThreadPool.h"
#include "EncoderTask.h"
#include <unistd.h>
#include <thread>
#include<memory>

#define TRACE_CLASS Logger::TRACE_CLASS_WAVTOMP3ENCODER

std::string WavToMp3Encoder::GenerateMp3FileName(const std::string& wavFileName)
{
    std::string mp3FileName;
    auto positionOfDot = wavFileName.find_last_of('.');
	if(std::string::npos != positionOfDot)
    {
		mp3FileName = wavFileName;
		auto mp3FileExtension = mapToFileExtension.find(EXT_MP3)->second;
		mp3FileName.replace(positionOfDot, mp3FileExtension.size(), mp3FileExtension);
	}
	else
	{
		LOG(Logger::LOG_LEVEL_ERROR, std::string("Failed to Generate MP3 filenamae for wav file : ") + wavFileName);
	}
    return mp3FileName;
}

void WavToMp3Encoder::Encode(const std::vector<std::string>& listOfFiles)
{	
    LOG(Logger::LOG_LEVEL_DEBUG, std::string("CPU cores preset = ") + std::to_string(std::thread::hardware_concurrency()));
	
	//1.Create Threadpool
    tU32 numberOfCores = std::thread::hardware_concurrency()? std::thread::hardware_concurrency() : 1;
    std::shared_ptr<IThreadPool> iThreadPool = std::make_shared<ThreadPool>(numberOfCores);
    iThreadPool->Create();

    //2.Create task for each file and assign to ThreadPool
	for(auto wavFileName : listOfFiles)
	{
        auto mp3FileName = GenerateMp3FileName(wavFileName);
		if(!mp3FileName.empty())
		{
			std::shared_ptr<ITask> iTask = std::make_shared<EncoderTask>(this, wavFileName, mp3FileName);
			iThreadPool->ScheduleTask(iTask);
		}
	}

    //3.Wait for All Tasks to be executed
	tU32 totalTasksScheduled = listOfFiles.size();
	tU32 tasksCompletedSoFar = 0;
	do
	{
	    tasksCompletedSoFar = iThreadPool->GetTaskCompletionCount();
		std::string progressInfoMessage = std::string("Encoding in progress(") + std::to_string(tasksCompletedSoFar) + "/" + std::to_string(totalTasksScheduled)+")";
		LOG(Logger::LOG_LEVEL_INFO, progressInfoMessage);
		sleep(1);
	}while(totalTasksScheduled != tasksCompletedSoFar);
	
	LOG(Logger::LOG_LEVEL_INFO, std::string("Encoding of All Files Completed, Check the input folder for Encoded Files."));
	
	//4.Destroy thread pool
    iThreadPool->Destroy();
}
