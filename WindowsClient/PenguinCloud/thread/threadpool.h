#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map>
#define MAX_CHANGE 10
#define MIN_TIMER 1
#define MAX_TIMER 1000
class ThreadObject;

class ThreadPool
{
public:
    //默认为没有员工
    ThreadPool(int workerNumber = 0);
    ~ThreadPool();

    //添加工作
    void addJob(ThreadObject *job);
    //设置最大等待比
    void setScale(const double &scale = 0.618);

private:
    //成为老板
    void createBoss();
    //雇佣工人
    void hireWorker(const int &workerNumber = 1);
    //解聘工人
    void fireWorker(const int &workerNumber = 1);
    //老板的工作
    void bossJob();
    //工人的工作
    void workerJob();

    //工人
    std::queue<std::thread> workers;
    //工人休息的锁
    std::mutex workerMutex;
    //工人结束休息的条件信号量
    std::condition_variable_any workerCondition;

    //工人编号
    //用来判断是不是被解雇的依据
    std::map<std::thread::id, bool> workersSerialNumber;
    //编号锁
    std::mutex serialMutex;

    //工作队列
    std::queue<ThreadObject *> tasks;
    //工作队列锁
    std::mutex taskQueueMutex;

    //老板
    std::thread boss;
    //老板视察锁
    std::mutex bossMutex;
    //老板结束休息的条件信号量
    std::condition_variable_any bossCondition;

    //最大工人数量
    int m_iMaxWorker;
    //工作中的工人数量
    int m_iWorking;
    //工作队列工作的数量
    int m_iTaskNumber;
    //老板定时视察工作的时间(ms)
    int m_iBossInspectionCycle;
    //工作中的工人和总队列的比值
    //这个比值是增加员工还是
    //裁员的依据
    //working : wait
    double m_dWWScale;
    //理论工作量
    int m_iTheoryWorking;
    //线程池结束标志
    bool m_bRun;
    //最大人员变动，变动数超过这个之后
    //老板视察工作的时间会缩短
    int m_iMaxChange;
    //老板视察工作最小时间差
    //单位ms
    int m_iMinTimer;
    //老板视察工作最大时间差
    //单位ms
    int m_iMaxTimer;
};

