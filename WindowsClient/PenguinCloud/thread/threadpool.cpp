#include "ThreadPool.h"
#include "ThreadObject.h"

#include <iostream>

using namespace std;

ThreadPool::ThreadPool(int workerNumber) :
m_iBossInspectionCycle(1000),
m_bRun(true)
{
	//最大工人数量
	m_iMaxWorker = 0;
	//工作中的工人数量
	m_iWorking = 0;
	//工作队列工作的数量
	m_iTaskNumber = 0;

	setScale();

	createBoss();

	for (int i = 0; i < 3; ++i)
	{
		workers.emplace(&ThreadPool::workerJob, this);
	}
}


ThreadPool::~ThreadPool()
{
	m_bRun = false;
	boss.join();

	//告诉所有工人把手中的工作做完就下班了
	workerCondition.notify_all();
	while (workers.size())
	{
		workers.front().join();
		workers.pop();
	}
}

//添加工作
void ThreadPool::addJob(ThreadObject *job)
{
	cout << "addJob" << endl;

	taskQueueMutex.lock();

	tasks.push(job);

	++m_iTaskNumber;

	taskQueueMutex.unlock();

	//唤醒一个正在休息的工人
	workerCondition.notify_one();
}

//成为老板
void ThreadPool::createBoss()
{
	boss = thread(&ThreadPool::bossJob, this);
}

//雇佣工人
void ThreadPool::hireWorker(const int &workerNumber)
{

}

//解聘工人
void ThreadPool::fireWorker(const int &workerNumber)
{

}

//设置最大等待比
void ThreadPool::setScale(const double &scale)
{
	m_dWWScale = scale;
}

//老板的工作
void ThreadPool::bossJob()
{
	while (m_bRun)
	{
		//cout << "老板来了" << "id = " << this_thread::get_id() << endl;

		this_thread::sleep_for(chrono::milliseconds(m_iBossInspectionCycle));
	}
}

//工人的工作
void ThreadPool::workerJob()
{
	ThreadObject *object;
	while (m_bRun)
	{
		//unique_lock<mutex> lock(workerMutex);

		workerMutex.lock();
		cout << "被锁住了" << endl;
		//如果任务队列为空就锁住
		while (this->m_bRun && this->tasks.empty())
			workerCondition.wait(workerMutex);

		workerMutex.unlock();

		cout << "开锁了" << endl;

		taskQueueMutex.lock();

		object = tasks.front();
		tasks.pop();
		--m_iTaskNumber;
		++m_iWorking;

		taskQueueMutex.unlock();

		object->run();

		taskQueueMutex.lock();

		--m_iWorking;

		taskQueueMutex.unlock();

		cout << "m_iWorking = " << m_iWorking << endl;
		cout << "m_iTaskNumber = " << m_iTaskNumber << endl;
		cout << "id = " << this_thread::get_id() << endl;
	}
}
