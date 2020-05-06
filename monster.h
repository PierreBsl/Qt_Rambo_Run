#ifndef MONSTER_H
#define MONSTER_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include "Utils.h"


class Monster:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int speed;
    int start = 0;
    bool direction = false;
public:
    Monster(QGraphicsItem * parent=0);
    int getSpeed() const { return speed; }
    void setSpeed(int speed) { this->speed = speed; }

public slots:
    void move();

};

#endif // MONSTER_H
