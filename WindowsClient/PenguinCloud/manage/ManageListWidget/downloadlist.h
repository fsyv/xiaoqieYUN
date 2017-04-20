#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>

#include "../network/msgtype.h"

QT_BEGIN_NAMESPACE
class PictureLabel;
class QLabel;
class QProgressBar;
class QListWidgetItem;
class QListWidget;
class PauseLabel;
class StopLabel;
class File;
class ConnectToServer;
class DownloadThread;
QT_END_NAMESPACE

class DownloadList : public QWidget
{
    Q_OBJECT
public:
    enum class CurrentStatus{
        NOSTATUS,           //没状态
        WAITTING,           //等待中
        RUNNING,            //运行中
        FINISHED,           //已完成
        PAUSED,             //已暂停
        STOP                //停止
    };

public:
    explicit DownloadList(QListWidget *listWidget, QWidget *parent = 0);
    ~DownloadList();

    void setFile(File *file);
    File *getFile() const;

    PauseLabel *getPauseButton() const;
    StopLabel *getStopButton() const;

    QListWidgetItem *getListWidgetItem() const;

    void startDownload();

private:
    void initWidget();
    void setWidgetLayout();
    void destroyWidget();

    void setIco();
    void setName(QString name);
    void setSize(qint64 currentSize, qint64 totalSize);
    void updateProgressBar(int progress);
    void setSpeed(QString speed);
    void setSpeed(qint64 speed);

    File *m_pFile;
    qint64 m_i64CurrentSize;
    CurrentStatus m_eCurrentStatus;

    PictureLabel *m_pFileIco;
    QLabel *m_pFileName;
    QLabel *m_pFileSize;
    QLabel *m_pSurplusTime;
    QProgressBar *m_pProgressBar;
    QLabel *m_pCurrentSpeed;
    PauseLabel *m_pPauseButton;
    StopLabel *m_pStopButton;

    QListWidgetItem *m_pListWidgetItem;

    ConnectToServer *m_pConnectToServer;
    DownloadThread *m_pDownloadThread;

protected:
    void resizeEvent(QResizeEvent *e);

protected slots:
    void start_pauseButton();
    void pause_pauseButton();
    void stop_stopButton();
    void recvDownloadFile_readyReadDownloadMsg(DownloadMsg downloadMsg);
    void updateTask_currentSize(qint64 currentSize);

signals:
    void start(QListWidgetItem *);
    void pause(QListWidgetItem *);
    void stop(QListWidgetItem *);
    void finished(QListWidgetItem *);
};

