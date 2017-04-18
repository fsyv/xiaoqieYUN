#ifndef DOWNLOADLIST_H
#define DOWNLOADLIST_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class PictureLabel;
class QLabel;
class QProgressBar;
class PauseLabel;
class StopLabel;
class File;
QT_END_NAMESPACE

class DownloadList : public QWidget
{
    Q_OBJECT
public:
    enum class CurrentStatus{
        WAITTING,           //等待中
        RUNNING,            //运行中
        FINISHED,           //已完成
        PAUSED,             //已暂停
        STOP                //停止
    };

public:
    explicit DownloadList(QWidget *parent = 0);
    ~DownloadList();

    void setFile(File *file);

    PauseLabel *getPauseButton() const;
    StopLabel *getStopButton() const;

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

protected:
    void resizeEvent(QResizeEvent *e);

protected slots:
    void start_pauseButton();
    void pause_pauseButton();
    void stop_stopButton();

public slots:
    void updateTask_currentSize(qint64 currentSize);

signals:
    void start(File *);
    void pause(File *);
    void stop(File *);
    void finished(File *);
};

#endif // DOWNLOADLIST_H
