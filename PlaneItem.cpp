#include "PlaneItem.h"
#include "bullet.h"
#include "monster.h"
#include "Utils.h"
#include <QKeyEvent>

#include <QPointF>

void PlaneItem::move() {

    QPointF pos = this->pos();

    int newX = pos.x() - speed;

    if (newX < 0) {
        speed = Utils::randInt(1, 10) - 10;
    }

    if (newX > this->scene()->width()) {
        speed = Utils::randInt(1, 10);
    }

    this->setPos(newX, pos.y());
}
void PlaneItem::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up){
        if (pos().y() > 0){
            setPos(x(), y()-25);
            // player->shootUp();
        }
    }
    else if(event->key() == Qt::Key_Left){
        if (pos().x() > 0){
            setPos(x()-25, y());
        }
    }
    else if(event->key() == Qt::Key_Right){
        if (pos().x() < 900){
            setPos(x()+25, y());
        }
    }
    else if(event->key() == Qt::Key_Space){

        //create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+100,y()+40);
        scene()->addItem(bullet);

        //play bulletsound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);

        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}
void PlaneItem::spawn()
{
    //create a Monster
    Monster * monster = new Monster();
    scene()->addItem(monster);
}




