#include "VideoMainWidget.h"

#include "stable.h"
#include "basiccontrol/musicbutton.h"
#include "basiccontrol/musicmainwidget.h"
#include "VideoWidget.h"
#include <QSlider>
#include <QMediaPlayer>


VideoMainWidget::VideoMainWidget(QWidget *parent) : BasicWidget(parent)
{
	resize(800, 600);
	setBackgroundColor("#1296db");

	init();
	setLayout();
	connects();

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

	setTitle("1.MP4");

	isSliderPressed = false;
}


VideoMainWidget::~VideoMainWidget()
{
	delete player;
}
void VideoMainWidget::setVideoUrl(const QString url)
{
	player->setMedia(QUrl(url));
	player->play();
	player->setVolume(50);
}
void  VideoMainWidget::init()
{

	videoWidget = new VideoWidget(this);
	videoWidget->setFixedSize(800, 530);

	player = new QMediaPlayer(this);
	player->setVideoOutput(videoWidget);

	play = new MusicButton(this);
	play->setIcon(QIcon(":/resource/image/pause.png"));
	play->setFixedSize(32, 32);

	volume = new MusicButton(this);
	volume->setIcon(QIcon(":/resource/image/volumn.png"));
	volume->setFixedSize(32, 32);

	playProgessBar = new QSlider(Qt::Horizontal, this);
	playProgessBar->setFixedWidth(500);

	volumeProgressBar = new QSlider(Qt::Horizontal, this);
	volumeProgressBar->setFixedWidth(100);
	volumeProgressBar->setValue(50);
	volumeProgressBar->setMaximum(100);

	showTime = new QLabel(this);
	showTime->setText("00:00/00:00");

}

void VideoMainWidget::setLayout()
{
	videoWidget->move(0, 30);
	play->move(5, 565);
	volumeProgressBar->move(690, 570);
	playProgessBar->move(120, 570);
	volume->move(655, 565);
	showTime->move(40, 575);
	/*fullScreen->move(width() - 35, height() - 32);*/
}

void  VideoMainWidget::connects()
{
	connect(play, &MusicButton::clicked,
		this, [this]() {
		if (player->state() == QMediaPlayer::PausedState)
		{
			play->setIcon(QIcon(":/resource/image/pause.png"));
			player->play();
		}
		else if (player->state() == QMediaPlayer::PlayingState)
		{
			play->setIcon(QIcon(":/resource/image/play.png"));
			player->pause();
		}
	});


	connect(player, &QMediaPlayer::positionChanged,
		this, [this](qint64 n) {
		totleTime = MusicMainWidget::convertTime(player->duration());
		showTime->setText(MusicMainWidget::convertTime(player->position()) + "/" + totleTime);
		if (!isSliderPressed)
			this->playProgessBar->setValue(n);
	});
	connect(player, &QMediaPlayer::durationChanged, this, [this](qint64) {playProgessBar->setMaximum(player->duration()); qDebug() << player->duration(); });
	connect(playProgessBar, &QSlider::sliderReleased, this, [this]() {player->setPosition(this->playProgessBar->value()); isSliderPressed = false; });
	connect(playProgessBar, &QSlider::sliderPressed, this, [this]() {this->isSliderPressed = true; });
	connect(playProgessBar, &QSlider::valueChanged,
		this, [this]() {
		showTime->setText(MusicMainWidget::convertTime(playProgessBar->value()) + "/" + totleTime);

	});

	connect(volumeProgressBar, &QSlider::valueChanged, this, [this](qint64) {player->setVolume(volumeProgressBar->value());
	volumeProgressBar->setToolTip(QString::number(volumeProgressBar->value())); });

	connect(volume, &MusicButton::clicked,
		this, [this]() {
		if (player->volume() != 0)
		{
			volumeValue = player->volume();
			player->setVolume(0);
			volumeProgressBar->setValue(0);
		}
		else
		{
			player->setVolume(volumeValue);
			volumeProgressBar->setValue(volumeValue);
		}
	});
}

void VideoMainWidget::closeEvent(QCloseEvent *event)
{
	player->stop();
}
