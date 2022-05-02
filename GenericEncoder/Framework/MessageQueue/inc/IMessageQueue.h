#ifndef IMESSAGEQUEUE_H
#define IMESSAGEQUEUE_H

template<typename T>
class IMessageQueue
{
public:
	virtual void Push(T message) = 0;
	virtual T WaitAndPop(const tU32 timeoutInMilliSeconds) = 0;
protected:
    virtual void ReleaseMessageWait() = 0;
    virtual tBool WaitForMessage(const tU32 timeoutInMilliSeconds) = 0;
	virtual T Pop() = 0;
};

#endif