#ifndef PATEFORM_H
#define PATEFORM_H
#include "void.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Plateform: public QGraphicsPixmapItem
{
private:
    int speed;
public:
    Plateform(QGraphicsItem * parent=0);
    int getSpeed() const { return speed; }
    void setSpeed(int speed) { this->speed = speed; }
    void move();

};

#endif // PATEFORM_H
