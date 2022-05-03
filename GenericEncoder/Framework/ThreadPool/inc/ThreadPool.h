#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "IThreadPool.h"
#include "BaseTypes.h"
#include "ITask.h"
#include "ThreadMessageQueue.h"

#include <pthread.h>
#include <mutex>  
#include <atomic>
#include <memory>

class ThreadPool : public IThreadPool
{
public:

    ThreadPool(tU32 numberOfThreads);
    ~ThreadPool();
    
    void Create();
    void Destroy();
    
    static void* Worker(void* argument);
    std::shared_ptr<ITask> WaitAndGetTaskFromQueue();
    void ScheduleTask(std::shared_ptr<ITask> iTask);
    tU32 GetTaskCompletionCount();
    void IncrementCompletedTaskCount();
    
    bool isShutdownRequested();
private:
    tU32 maxNumberOfThreads;
    std::vector<pthread_t> threadList;
    
    std::atomic_bool stopAllThreads{false};
    std::mutex threadMutex;
    tU32 completedTaskCount = 0;
    ThreadMessageQueue<std::shared_ptr<ITask>> taskQueue;
};
#endif