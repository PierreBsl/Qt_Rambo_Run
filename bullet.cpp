#include "bullet.h"
#include "monster.h"
#include "score.h"
#include "mainwindow.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

extern Score * score;
extern Player * player;
extern MainScene * mainScene;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //drew the rect
    setPixmap(QPixmap(":/img/bullet1.png"));
    //connect
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    // if bullet collides a monster
    QList<QGraphicsItem *>colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Monster)){
            //increase score
            score->increase();

            //remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            //delete them both
            delete colliding_items[i];
            delete this;

        }
    }
    //move bullet up
    setPos(x()+20, y());
    if(pos().x() > 1200){
        scene()->removeItem(this);
        delete this;
        qDebug() << "Bullet deleted";
    }

}
