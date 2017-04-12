#include "ThreadObject.h"

#include<thread>

ThreadObject::ThreadObject()
{

}


ThreadObject::~ThreadObject()
{
}

void ThreadObject::run()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//while (true);
}

void ThreadObject::start()
{

}

void ThreadObject::pause()
{

}

void ThreadObject::stop()
{

}