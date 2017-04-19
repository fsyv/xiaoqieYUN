#include "musicmainwidget.h"

#include "musicbutton.h"

#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QPixmap>
#include <QMediaPlayer>
MusicMainWidget::MusicMainWidget(QWidget *parent) : BasicWidget(parent)
  ,isPressed(false)
  ,player(Q_NULLPTR)
{

    setBackgroundColor(QColor(100, 100, 100, 100));

    init();
    layout();

    setStyleSheet("QSlider::groove:horizontal {\
                  height: 4px;\
            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));\
}\
QSlider::handle:horizontal {\
                    width: 12px;\
height:12px;\
background: rgb(255, 254, 161);\
margin: -4px 0px -4px 0px;\
border-radius: 6px;\
}\
QSlider::add-page:horizontal {\
                      background: white;\
}\
QSlider::sub-page:horizontal {\
                      background: rgb(255, 254, 161);\
}\
QLabel{color:white;}\
");

    resize(274, 80);

    //播放控制相关的
    connect(pause, &QPushButton::clicked, this, &MusicMainWidget::music_pause);
    connect(forward, &MusicButton::clicked, this, [this]() {player->setPosition(player->position() + 5000);});
    connect(backward, &MusicButton::clicked, this, [this]() {player->setPosition(player->position() - 5000);});
    connect(player, &QMediaPlayer::positionChanged,
            this, [this](qint64 n){
                  if(!isSliderPressed)
                      this->play_progress->setValue(n);
                });
    connect(play_progress, &QSlider::sliderReleased, this, [this](){player->setPosition(this->play_progress->value()); isSliderPressed = false;});
    connect(play_progress, &QSlider::sliderPressed, this, [this](){this->isSliderPressed = true;});
    connect(play_progress, &QSlider::valueChanged,
            this, [this](){
                show_time->setText(convertTime(play_progress->value()) + "/" + totleTime);
                play_progress->setToolTip(convertTime(play_progress->value()));
            });

    connect(paly_volumn, &QSlider::valueChanged, this, [this](qint64){player->setVolume(paly_volumn->value());});
}

void MusicMainWidget::init()
{
    pause = new  MusicButton(this);
    forward = new  MusicButton(this);
    backward = new  MusicButton(this);
    paly_volumn = new  QSlider(Qt::Horizontal, this);
    play_progress = new  QSlider(Qt::Horizontal, this);
    musicName = new  QLabel(this);
    volumn = new  QLabel(this);
    show_time = new QLabel(this);
    player = new QMediaPlayer(this);

}

void MusicMainWidget::setMusic(const QString &url)
{
    player->setMedia(QUrl(url));
    musicName->setText(url.split('/').last());
}

void MusicMainWidget::layout()
{
    musicName->setText("正在加载中...");
    musicName->move(5, 2);
    musicName->setFixedSize(200, 20);

    backward->setFixedSize(25, 25);
    backward->move(5, 55);
    backward->setIcon(QIcon(":/resource/image/backward.png"));

    pause->setFixedSize(25, 25);
    pause->move(35, 55);
    pause->setIcon(QIcon(":/resource/image/pause.png"));

    forward->setFixedSize(25, 25);
    forward->move(65, 55);
    forward->setIcon(QIcon(":/resource/image/forward.png"));

    play_progress->setFixedWidth(250);
    play_progress->move(15, 27);

    volumn->setFixedSize(25, 25);
    volumn->move(135, 55);
    volumn->setPixmap(QPixmap(":/resource/image/volumn.png").scaled(16,16));

    show_time->move(185, 45);
    show_time->setText("00:00/00:00");
    paly_volumn->setFixedWidth(100);

    paly_volumn->move(152, 57);
    paly_volumn->setMaximum(100);
    paly_volumn->setValue(50);
}


void MusicMainWidget::music_pause()
{
    if(isPressed)
    {
        isPressed = false;
        pause->setIcon(QIcon(":/resource/image/pause.png"));
        player->play();
        play_progress->setMaximum(player->duration());
        totleTime = convertTime(player->duration());
    }
    else
    {
        isPressed = true;
        pause->setIcon(QIcon(":/resource/image/play.png"));
        player->pause();
        setMusic("http://120.24.84.247/test/G.E.M.邓紫棋 - 画 (Live Piano Session II).mp3");
    }
}


QString MusicMainWidget::convertTime(qint64 value)
{
    const qint64 min = 60 * 1000;
    const qint64 sec = 1000;
    qint64 Min = value / min;
    qint64 Sec = value / sec - 60 * Min;

    QString str_min;
    QString str_sec;

    if(Min < 10)
    {
        str_min = "0" + QString::number(Min);
    }
    else
    {
        str_min = QString::number(Min);
    }

    if(Sec < 10)
    {
        str_sec = "0" + QString::number(Sec);
    }
    else
    {
        str_sec = QString::number(Sec);
    }

    QString time = str_min + ":" + str_sec;

    return time;
}
