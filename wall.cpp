#include "wall.h"
#include "gameover.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <stdlib.h>

Wall::Wall(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    //drew the rect
    setPixmap(QPixmap(":/img/grillage.jpg"));

}
