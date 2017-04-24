#include "cleanlabel.h"

#include "../stable.h"

CleanLabel::CleanLabel(QWidget *parent) :
    QLabel(parent)
{
    setPixmap(QPixmap("://resource/manage/clear.png"));
    resize(16, 16);
    setScaledContents(true);
    //鼠标跟踪
    setMouseTracking(true);
}


CleanLabel::~CleanLabel()
{

}

void CleanLabel::mouseReleaseEvent(QMouseEvent *event)
{
    emit clean();
    QLabel::mouseReleaseEvent(event);
}
