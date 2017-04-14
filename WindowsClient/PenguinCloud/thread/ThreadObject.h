#pragma once

#include <QObject>

class ThreadObject : public QObject
{
    Q_OBJECT
public:
    ThreadObject(QObject *parent = nullptr);
    virtual ~ThreadObject();

	//子类需要重写这个方法
    virtual void run() = 0;
	virtual void start();
	virtual void pause();
	virtual void stop();
};

