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
    Plateform(QString imageFileName): QGraphicsPixmapItem(QPixmap(imageFileName))
    {
        this->speed = 3;
    }
    int getSpeed() const { return speed; }
    void setSpeed(int speed) { this->speed = speed; }
    void move();

};

#endif // PATEFORM_H
