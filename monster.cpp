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
extern Health * health;
extern Monster * monster;

Monster::Monster(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //set Position
    setPos(1200, 390);
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
    if(pos().x() == 700){
        monster = new Monster();
        mainScene->addItem(monster);
    }
}

