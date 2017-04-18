#ifndef PICTURELABEL_H
#define PICTURELABEL_H

#include <QLabel>

class PictureLabel : public QLabel
{
public:
    PictureLabel(QWidget *parent = nullptr);
    PictureLabel(const QPixmap &picture, QWidget *parent = nullptr);
    ~PictureLabel();
};

#endif // PICTURELABEL_H
