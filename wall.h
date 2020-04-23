#ifndef WALL_H
#define WALL_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "Utils.h"

class Wall: public QGraphicsPixmapItem
{
public:
    Wall(QGraphicsItem * parent=0);
};

#endif // WALL_H
