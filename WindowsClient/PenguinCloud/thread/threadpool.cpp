#include "ThreadPool.h"

#include "ThreadObject.h"

using namespace std;

ThreadPool::ThreadPool(int workerNumber, QObject *parent) :
    QObject(parent),
    m_iBossInspectionCycle(1000),
    m_bRun(true),
    m_iMaxChange(MAX_CHANGE),
    m_iMinTimer(MIN_TIMER),
    m_iMaxTimer(MAX_TIMER)
{
    //最大工人数量
    m_iMaxWorker = 0;
    //工作中的工人数量
    m_iWorking = 0;
    //工作队列工作的数量
    m_iTaskNumber = 0;

    setScale();

    //如果设置了初始化工人数量
    //则初始化的时候就默认已有几个工人
    hireWorker(workerNumber);

    //创建BOSS线程
    createBoss();
}


ThreadPool::~ThreadPool()
{
    m_bRun = false;
    bossCondition.notify_one();
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
    taskQueueMutex.lock();

    tasks.push(job);

    ++m_iTaskNumber;

    taskQueueMutex.unlock();

    //如果任务队列数量大于1
    //就要把在休息中的老板唤醒
    //对工作进行视察
    if (m_iTaskNumber > 1)
        bossCondition.notify_one();

    //唤醒一个正在休息的工人
    workerCondition.notify_one();
}

//成为老板
void ThreadPool::createBoss()
{
    boss = std::thread(&ThreadPool::bossJob, this);
}

//雇佣工人
void ThreadPool::hireWorker(const int &workerNumber)
{
    //一次不会超过10个工人
    int n = (workerNumber < m_iMaxChange) ? workerNumber : m_iMaxChange;
    //如果小于0视为异常
    n = n > 0 ? n : 0;

    for (int i = 0; i < n; ++i)
    {
        workers.emplace(&ThreadPool::workerJob, this);
    }

    m_iMaxWorker += n;

    //修改以后老板视察频率
    if (n == m_iMaxChange)
    {
        m_iBossInspectionCycle /= m_iMaxChange;

        //老板视察时间不能小于最小时间
        m_iBossInspectionCycle = m_iBossInspectionCycle > m_iMinTimer ? m_iBossInspectionCycle : m_iMinTimer;
    }
    else if (n <= 1)
    {
        //不坐处理

    }
    else if (n < (m_iMaxChange) / 2)
    {
        //减缓老板视察时间
        m_iBossInspectionCycle *= m_iMaxChange;

        //老板视察时间不能大于最小时间
        m_iBossInspectionCycle = (m_iBossInspectionCycle < m_iMaxTimer) ? m_iBossInspectionCycle : m_iMaxTimer;
    }
}

//解聘工人
void ThreadPool::fireWorker(const int &workerNumber)
{
    //一次不会超过10个工人
    int n = (workerNumber < m_iMaxChange) ? workerNumber : m_iMaxChange;
    //如果小于0视为异常
    n = n > 0 ? n : 0;


    //最少会留一个工人
    if (m_iMaxWorker - n < 1)
        n = m_iMaxWorker - 1;

    m_iMaxWorker -= n;


    for (int i = 0; i < n; ++i)
    {
        serialMutex.lock();
        workersSerialNumber[workers.front().get_id()] = false;
        serialMutex.unlock();

        //让这个线程自生自灭
        workers.front().detach();
        workers.pop();
    }

    //修改以后老板视察频率
    if (n == m_iMaxChange)
    {
        //加快老板视察时间
        m_iBossInspectionCycle /= m_iMaxChange;

        //老板视察时间不能小于最小时间
        m_iBossInspectionCycle = (m_iBossInspectionCycle > m_iMinTimer) ? m_iBossInspectionCycle : m_iMinTimer;
    }
    else if (n <= 1)
    {
        //不坐处理

    }
    else if (n < (m_iMaxChange) / 2)
    {
        //减缓老板视察时间
        m_iBossInspectionCycle *= m_iMaxChange;

        //老板视察时间不能大于最小时间
        m_iBossInspectionCycle = (m_iBossInspectionCycle < m_iMaxTimer) ? m_iBossInspectionCycle : m_iMaxTimer;
    }
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
        if (!m_iMaxWorker)
        {
            //如果没有工人，则招一个工人
            hireWorker(1);
        }

        bossMutex.lock();
        //如果工人数量等于1个，且没有任务
        //老板则进入休息状态
        if (m_iMaxWorker == 1 && m_iTaskNumber == 0)
        {
            m_iBossInspectionCycle = m_iMaxTimer;
            bossCondition.wait(bossMutex);
        }
        bossMutex.unlock();

        //得出理论工作量
        //这里没有处理线程同步，是一个瞬时值
        //在雇佣或者解雇人的时候时候会根据事件情况为依据
        //这里只是老板给出的一个参考
        m_iTheoryWorking = int(m_iTaskNumber * m_dWWScale);
        if (m_iMaxWorker < m_iTheoryWorking)
        {
            //实际工作量小于理论工作量
            //招人
            hireWorker(m_iTheoryWorking - m_iMaxWorker);
        }
        else if (m_iMaxWorker > m_iTheoryWorking)
        {
            //实际工作量大于理论工作量
            //裁员
            fireWorker(m_iMaxWorker - m_iTheoryWorking);
        }

        this_thread::sleep_for(chrono::milliseconds(m_iBossInspectionCycle));
    }
}

//工人的工作
void ThreadPool::workerJob()
{
    ThreadObject *object;

    //多个线程会写
    serialMutex.lock();
    workersSerialNumber.insert(map<thread::id, bool>::value_type(this_thread::get_id(), true));
    serialMutex.unlock();

    while (m_bRun && workersSerialNumber[this_thread::get_id()])
    {
        workerMutex.lock();
        //如果任务队列为空就锁住
        while (this->m_bRun && this->tasks.empty())
            workerCondition.wait(workerMutex);

        workerMutex.unlock();

        taskQueueMutex.lock();

        if (tasks.empty())
        {
            taskQueueMutex.unlock();
            continue;
        }

        object = tasks.front();
        tasks.pop();
        --m_iTaskNumber;
        ++m_iWorking;

        taskQueueMutex.unlock();

        object->run();

        taskQueueMutex.lock();

        --m_iWorking;

        taskQueueMutex.unlock();
    }

    serialMutex.lock();
    workersSerialNumber.erase(this_thread::get_id());
    serialMutex.unlock();
}
