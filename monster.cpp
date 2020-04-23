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

extern Health * health;

Monster::Monster(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //set Position
    setPos(1200, 340);
    //drew the rect
    setPixmap(QPixmap(":/img/enemy1.png"));

    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Monster::move()
{
    //move monster left
    setPos(x()-5, y());

    if(pos().x() < 0){
        scene()->removeItem(this);
        delete this;
        qDebug() << "monster deleted";
    }    
}

