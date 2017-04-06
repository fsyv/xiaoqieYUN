#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QThread>
#include "QDebug"


#include "../network/msgtype.h"

class DownloadFileToServer;

class DownloadThread : public QThread
{
public:
    DownloadThread(DownloadMsg downloadMsg, QObject *parent = nullptr);
	void run();
private:
    DownloadFileToServer *m_download;
    DownloadMsg m_stDownloadMsg;
};

#endif // DOWNLOADTHREAD_H
