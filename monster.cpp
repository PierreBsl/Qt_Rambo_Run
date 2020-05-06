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

Monster::Monster(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //drew the rect
    setPixmap(QPixmap(":/img/enemyLeft.png"));
    this->speed = 3;

}

void Monster::move()
{
        int newX = this->x();

        if (start >= 60){
            if(direction){
                direction = false;
            }else {
                direction = true;
            }
            start = 0;
        }
        if (direction) {
            setPixmap(QPixmap(":/img/enemyLeft.png"));
            speed = - 3;
        }
        else {
            setPixmap(QPixmap(":/img/enemyRight.png"));
            speed = 3;
        }
        start ++;
        newX = newX + speed;
        this->setPos(newX, this->y());
}

