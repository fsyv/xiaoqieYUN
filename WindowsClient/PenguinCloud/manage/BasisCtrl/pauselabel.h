#ifndef PAUSELABEL_H
#define PAUSELABEL_H

#include <QLabel>

class PauseLabel : public QLabel
{
    Q_OBJECT
private:
    enum class ButtonLogin{
        START,          //开始样子
        PAUSE           //暂停样子
    };

public:
    PauseLabel(QWidget *parent = nullptr);
    ~PauseLabel();

    void startClick();
    void pauseClick();
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    QString pausePicture;
    QString startPicture;

    ButtonLogin m_eButtonLogin;

signals:
    void pause();
    void start();
};

#endif // PAUSELABEL_H
