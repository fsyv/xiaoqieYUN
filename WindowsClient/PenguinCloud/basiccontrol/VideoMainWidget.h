#pragma once
#include "basicwidget/basicwidget.h"


QT_BEGIN_NAMESPACE
class MusicButton;
class QWidget;
class VideoWidget;
class QSlider;
class QMediaPlayer;
class QLabel;
QT_END_NAMESPACE


class VideoMainWidget :
	public BasicWidget
{
	Q_OBJECT
public:
	VideoMainWidget(QWidget *parent = 0);
	~VideoMainWidget();
	void setVideoUrl(const QString url);

protected:
    void closeEvent(QCloseEvent *);

private:
	void init();
	void setLayout();
	void connects();   //所有的connect在这里

	VideoWidget *videoWidget;
	MusicButton *play;              //播放按钮
	//MusicButton *fullScreen;		//全屏按钮
	MusicButton *volume;			//声音调节
	QSlider *playProgessBar;		//播放进度
	QSlider *volumeProgressBar;		//声音
	QLabel *showTime;
	QString totleTime;
	QMediaPlayer *player;
	int volumeValue;
	bool isSliderPressed;
};

