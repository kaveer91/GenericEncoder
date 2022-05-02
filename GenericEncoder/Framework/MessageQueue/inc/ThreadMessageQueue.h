#ifndef THREADMESSAGEQUEUE_H
#define THREADMESSAGEQUEUE_H

#include "IMessageQueue.h"

#include <queue>
#include <mutex>
#include <semaphore.h>
#include <string>
#include <sys/time.h>
#include <cstring>
#include <iostream>

template<typename T>
class ThreadMessageQueue : public IMessageQueue<T>
{
public:
    ThreadMessageQueue();
	~ThreadMessageQueue();
	void Push(T message);
	T WaitAndPop(tU32 timeoutInMilliSeconds);
	
protected:

    void ReleaseMessageWait();
	tBool WaitForMessage(const tU32 timeoutInMilliSeconds);
	T Pop();
	
private:	
    std::mutex messageQueueMutex;
	sem_t messageCountSemaphore;
	std::queue <T> messageQueue;
};


template<typename T>
ThreadMessageQueue<T>::ThreadMessageQueue()
{
	memset(&messageCountSemaphore, 0, sizeof(messageCountSemaphore));
	sem_init(&messageCountSemaphore, 0, 0);
}


template<typename T>
ThreadMessageQueue<T>::~ThreadMessageQueue()
{
	sem_destroy(&messageCountSemaphore);
}

template<typename T>
void ThreadMessageQueue<T>::Push(T message)
{
	messageQueueMutex.lock();
	messageQueue.push(message);
	messageQueueMutex.unlock();
	
	ReleaseMessageWait();
}

template<typename T>
void ThreadMessageQueue<T>::ReleaseMessageWait()
{
    sem_post(&messageCountSemaphore);
}

template<typename T>
T ThreadMessageQueue<T>::WaitAndPop(const tU32 timeoutInMilliSeconds)
{
	T message;
 
    bool isMessageAvailable = WaitForMessage(timeoutInMilliSeconds);	 
	if(isMessageAvailable)
	{
         message = Pop();
	}
	
	return message;
}

template<typename T>
tBool ThreadMessageQueue<T>::WaitForMessage(tU32 timeoutInMilliSeconds)
{
	tBool isMessageAvailable = false;
	
	struct timespec timeout;
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += timeoutInMilliSeconds/1000;

	int errorCode = sem_timedwait(&messageCountSemaphore, &timeout);
	
	if(0 == errorCode)
	{
		isMessageAvailable = true;
	}
	
	return isMessageAvailable;
}

template<typename T>
T ThreadMessageQueue<T>::Pop()
{
	T message;
	messageQueueMutex.lock();
	if(!messageQueue.empty())
	{
        message = messageQueue.front();
        messageQueue.pop();
        messageQueueMutex.unlock();
	}
	else
    {
		messageQueueMutex.unlock();
    }
		 
    return message;
}

#endif