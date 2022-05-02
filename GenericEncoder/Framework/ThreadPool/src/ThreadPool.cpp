#include "ThreadPool.h"
#include "Logger.h"

#include <semaphore.h>
#include <string>
#include <sys/time.h>
#include <cstring>

#define TRACE_CLASS Logger::TRACE_CLASS_THREADPOOL

const tU16 messageWaitTimeoutInMilliSeconds = 1000 ;

ThreadPool::ThreadPool(tU32 numberOfThreads):maxNumberOfThreads(numberOfThreads)
{
}

void ThreadPool::Destroy()
{
	stopAllThreads = true;
	
	for(auto threadHandle: threadList)
	{
		pthread_join(threadHandle, NULL);
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::Create()
{
	for(tU16 count = 1; count <= maxNumberOfThreads; count++)
	{
		pthread_t threadHandle;
		int errorCode = pthread_create(&threadHandle, nullptr, &ThreadPool::Worker, this);
        if(errorCode)
		{
			LOG(Logger::LOG_LEVEL_FATAL, std::string("Thread creation failed errorCode = ") + std::to_string(errorCode));
		}
		else
		{
			threadList.push_back(threadHandle);
			LOG(Logger::LOG_LEVEL_DEBUG, std::string("Thread Created. thread index = ") + std::to_string(count));
		}
	}
}

std::shared_ptr<ITask> ThreadPool::WaitAndGetTaskFromQueue()
{	 
	return taskQueue.WaitAndPop(messageWaitTimeoutInMilliSeconds);
}

void ThreadPool::IncrementCompletedTaskCount()
{
	threadMutex.lock();
	completedTaskCount++;
    threadMutex.unlock();
}

bool ThreadPool::isShutdownRequested()
{
    return stopAllThreads;
}

void* ThreadPool::Worker(void* context)
{
	if(context)
	{
		LOG(Logger::LOG_LEVEL_DEBUG, std::string("Worker Thread started"));
		
		ThreadPool* threadPool = static_cast<ThreadPool*>(context);

	    while(false == threadPool->isShutdownRequested())
	    {	
	        std::shared_ptr<ITask> iTask = threadPool->WaitAndGetTaskFromQueue();
			
			if(iTask)
			{
    			LOG(Logger::LOG_LEVEL_DEBUG, std::string("Worker Thread starting to execute a task"));
                iTask->Execute();
				LOG(Logger::LOG_LEVEL_DEBUG, std::string("Worker Thread executed a task"));
				
	            threadPool->IncrementCompletedTaskCount();
			}
	    };
	}
	LOG(Logger::LOG_LEVEL_DEBUG, std::string("Worker Thread Exiting"));
	
	return NULL;
}

void ThreadPool::ScheduleTask(std::shared_ptr<ITask> iTask)
{
	taskQueue.Push(iTask);
}

tU32 ThreadPool::GetTaskCompletionCount()
{
	return completedTaskCount;
}