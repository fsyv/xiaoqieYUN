#include "pauselabel.h"

PauseLabel::PauseLabel(QWidget *parent):
    QLabel(parent)
{

    startPicture = QString("://resource/manage/paly_normal.png");
    pausePicture = QString("://resource/manage/pause_normal.png");

    resize(16, 16);
    setScaledContents(true);
}

PauseLabel::~PauseLabel()
{

}

void PauseLabel::startClick()
{
    m_eButtonLogin = ButtonLogin::PAUSE;
    setPixmap(QPixmap(pausePicture));
    emit start();
}

void PauseLabel::pauseClick()
{
    m_eButtonLogin = ButtonLogin::START;
    setPixmap(QPixmap(startPicture));
    emit pause();
}

void PauseLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        switch (m_eButtonLogin) {
        case ButtonLogin::START:
            m_eButtonLogin = ButtonLogin::PAUSE;
            setPixmap(QPixmap("://resource/manage/pause_enter.png"));
            emit start();
            break;
        case ButtonLogin::PAUSE:
            m_eButtonLogin = ButtonLogin::START;
            setPixmap(QPixmap("://resource/manage/paly_enter.png"));
            emit pause();
            break;
        }
    }
    else
        event->ignore();

    QLabel::mousePressEvent(event);
}

void PauseLabel::enterEvent(QEvent *event)
{
    switch (m_eButtonLogin) {
    case ButtonLogin::START:
        setPixmap(QPixmap("://resource/manage/paly_enter.png"));
        break;
    case ButtonLogin::PAUSE:
        setPixmap(QPixmap("://resource/manage/pause_enter.png"));
        break;
    }

    QLabel::enterEvent(event);
}

void PauseLabel::leaveEvent(QEvent *event)
{
    switch (m_eButtonLogin) {
    case ButtonLogin::START:
        setPixmap(QPixmap(startPicture));
        break;
    case ButtonLogin::PAUSE:
        setPixmap(QPixmap(pausePicture));
        break;
    }

    QLabel::leaveEvent(event);
}
