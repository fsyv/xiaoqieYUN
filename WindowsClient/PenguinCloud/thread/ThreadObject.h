#pragma once
class ThreadObject
{
public:
	ThreadObject();
	~ThreadObject();

	//子类需要重写这个方法
	virtual void run();
	virtual void start();
	virtual void pause();
	virtual void stop();
};

