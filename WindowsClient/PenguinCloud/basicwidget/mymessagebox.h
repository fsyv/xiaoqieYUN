#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include "basicwidget.h"
#include <QtWidgets>

typedef enum _IconType{
    Warn = 0,
    Error = 1,
    Ok
}IconType;

class MyMessageBox : public BasicWidget
{
    Q_OBJECT
public:
    MyMessageBox(QWidget *parent = 0);
    static MyMessageBox* showMessageBox(QWidget *parent,  const QString &message, const QString &btn1_text, const QString &btn2_text, IconType type);
protected:
    void paintEvent(QPaintEvent *event);
    void setInfo(const QString &message, const QString& btn1_text, const QString &btn2_text,  IconType type);

signals:
    void btn1();
    void btn2();
private:
    void init();

    QPushButton *btn_1;
    QPushButton *btn_2;
    QLabel *icon;
    QLabel *message;


};

#endif // MESSAGEBOX_H
