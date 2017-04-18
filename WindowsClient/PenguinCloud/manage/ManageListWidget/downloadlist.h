#ifndef DOWNLOADLIST_H
#define DOWNLOADLIST_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class PictureLabel;
class QLabel;
class PauseLabel;
class StopLabel;
QT_END_NAMESPACE

class DownloadList : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadList(QWidget *parent = 0);
    ~DownloadList();

private:
    void initWidget();
    void setWidgetLayout();
    void destroyWidget();

    PictureLabel *m_pFileIco;
    QLabel *m_pFileName;
    QLabel *m_pFileSize;
    QLabel *m_pSurplusTime;
    //+
    //进度条
    //+
    QLabel *m_pCurrentSpeed;
    PauseLabel *m_pPauseButton;
    StopLabel *m_pStopButton;

protected:
    void resizeEvent(QResizeEvent *e);

signals:

public slots:
};

#endif // DOWNLOADLIST_H
