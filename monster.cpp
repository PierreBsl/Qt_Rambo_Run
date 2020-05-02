#include "mainwindow.h"
#include "MainScene.h"
#include "monster.h"
#include "gameover.h"
#include "health.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <stdlib.h>

extern MainScene * mainScene;
extern Wall * wall;

Monster::Monster(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //set Position
    setPos(1200, 390);
    //drew the rect
    setPixmap(QPixmap(":/img/enemy1.png"));
    this->speed = 5;

    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Monster::move()
{
    QPointF pos = this->pos();

        int newX = pos.x() - 5;

        if (newX < wall->x() ) {
            speed = - 5;
        }

        if (newX > this->scene()->width()) {
            speed = 5;
        }

        this->setPos(newX, pos.y());
}

