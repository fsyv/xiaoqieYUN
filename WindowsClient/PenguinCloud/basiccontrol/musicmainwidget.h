#ifndef MUSICMAINWIDGET_H
#define MUSICMAINWIDGET_H

#include "basicwidget/basicwidget.h"

QT_BEGIN_NAMESPACE
class MusicButton;
class QSlider;
class QLabel;
class QMediaPlayer;
QT_END_NAMESPACE

class MusicMainWidget : public BasicWidget
{
    Q_OBJECT
public:
    explicit MusicMainWidget(QWidget *parent = 0);
    void setMusic(const QString &);
    static QString convertTime(qint64);
signals:

public slots:
    void music_pause();

private:
    void init();
    void layout();



    MusicButton *pause;          //播放暂停按钮
    MusicButton *forward;        //快进
    MusicButton *backward;       //快退
    QSlider *play_volumn;        //声音调节
    QSlider *play_progress;      //播放进度
    QLabel *musicName;           //显示歌名
    QLabel *volumn;              //声音指示
    QLabel *show_time;          //歌曲总时间
    QLabel *current_time;        //当前已经播放的时间
    QMediaPlayer *player;
    bool isPressed;
    bool isSliderPressed;
    QString totleTime;
};

#endif // MUSICMAINWIDGET_H
