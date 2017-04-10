#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <future>

class UpdateFileThread;


class ThreadPool
{
public:
    ThreadPool(int taskCount);
    ~ThreadPool();

    void enqueue();

private:
    //工作线程
    std::vector<std::thread> workers;
    //任务队列
    std::queue<std::function<void()>> tasks;

    //锁
    //队列锁
    std::mutex queueMutex;
    //信号量
    std::condition_variable cond;
};

#endif // THREADPOOL_H
