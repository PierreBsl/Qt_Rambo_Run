#include "plateform.h"
#include <QPointF>

Plateform::Plateform(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/img/plateform.png"));
}
