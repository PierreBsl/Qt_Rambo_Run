#include "plateform.h"
#include <QPointF>

extern Void * vide;

void Plateform::move()
{
    QPointF pos = this->pos();

    int newX = pos.x() - speed;

    if (newX < vide->x()) {
        speed = -3;
    }

    if (newX > vide->x()+190) {
        speed = 3;
    }

    this->setPos(newX, pos.y());
}
