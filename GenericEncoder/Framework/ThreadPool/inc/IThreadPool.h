#ifndef ITHREAD_POOL_H
#define ITHREAD_POOL_H

#include "BaseTypes.h"
#include "ITask.h"

#include<memory>

class IThreadPool
{
public:
    virtual void Create() = 0;
    virtual void Destroy() = 0;
    
    virtual void ScheduleTask(std::shared_ptr<ITask> iTask) = 0;
    virtual tU32 GetTaskCompletionCount() = 0;
protected:
    virtual std::shared_ptr<ITask> WaitAndGetTaskFromQueue() = 0;
    virtual void IncrementCompletedTaskCount() = 0;
    virtual bool isShutdownRequested() = 0;
};
#endif