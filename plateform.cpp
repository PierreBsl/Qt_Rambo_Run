#include "plateform.h"
#include <QPointF>

extern Void * vide;

Plateform::Plateform(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/img/plateform.png"));
    this->speed = 2;
}
void Plateform::move()
{
    this->setPos(vide->x(), 285);
}
