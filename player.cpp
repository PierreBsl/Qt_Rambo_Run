#include "player.h"
#include "bullet.h"
#include "monster.h"
#include "mainwindow.h"
#include "MainScene.h"
#include <QObject>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPointF>

extern Health * health;
extern Monster * monster;
extern QTimer * timer_chrono;
extern gameOver * gameover;
extern QMediaPlayer * gameOverSound;
extern QMediaPlayer * endGameSound;
extern EndGame * endgame;
extern Player * player;


Player::Player(QString description, QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)), description(description) {

    setPixmap(imageFileName);
    groundPosition = scenePos().y();
}
void Player::startPlaying(){

    QList<QGraphicsItem *>colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Monster)){
            //decrease health
            health->decrease();
        }
        if(typeid(*(colliding_items[i])) == typeid(Wall)){
            this->setX(x()-15);
            if (y()>150){
                this->setY(y()-15);
            }
        }
        if(typeid(*(colliding_items[i])) == typeid(Void)){

            qDebug() << "TOUCHED";
            gameover->display();

        }
        if(typeid(*(colliding_items[i])) == typeid(EndGame)){

            qDebug() << "End Game";

            if (endGameSound->state() == QMediaPlayer::PlayingState){
                endGameSound->setPosition(0);

            }
            else if (endGameSound->state() == QMediaPlayer::StoppedState){
                endGameSound->play();
            }
            endgame->endScreen();
            scene()->removeItem(this);
            timer_chrono->stop();
        }
    }
}

void Player::jump(){

    while (true){

    }
}
