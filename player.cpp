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

extern MainScene * mainScene;
extern Health * health;
extern Monster * monster;
extern QTimer * timer_chrono;
extern gameOver * gameover;
extern QMediaPlayer * gameOverSound;
extern QMediaPlayer * endGameSound;
extern EndGame * endgame;
extern Player * player;
extern Wall * wall;


Player::Player(QString description, QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)), description(description) {

    setPixmap(imageFileName);
    groundPosition = 300;
    onGround = true;

    wallContact=false;
    groundContact=true;
    this->status = "Standing";
    this->direction = "Right";
    this->setVelocity();
    this->gravity=-2;

}

void Player::setStatus(std::string status, std::string previousStatus) {
    this->status = std::move(status);
    this->previousStatus = std::move(previousStatus);
}

std::string Player::getStatus() {
    return this->status;
}

void Player::setwallContact()
{

    QList<QGraphicsItem *>colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Wall)){wallContact = true;}
        else{wallContact = false;}
    }
}
void Player::setgroundContact(){
    if (this->y()==300){groundContact = true;
    }else{groundContact = false;}
}

void Player::setDirection(std::string direction) {
    this->direction = std::move(direction);
}

void Player::setVelocity(){
    this->velocityX=2;
    this->velocityY=3;
}

void Player::setPreviousStatus(std::string previousStatus) {
    this->previousStatus = std::move(previousStatus);
}

void Player::move() {
    if(status=="Standing"){
        this->stand();
    }else if(status=="Running"){
        this->run();
    } else if(status=="Jumping"){
        this->jump();
    } else if(status=="Falling") {
        this->fall();
    }
}

void Player::collisions()
{
    QList<QGraphicsItem *>colliding_items = collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Monster)){
            //decrease health
            health->decrease();
        }
        if(typeid(*(colliding_items[i])) == typeid(Void)){
            qDebug() << "TOUCHED";
            gameover->display();
        }
        if(typeid(*(colliding_items[i])) == typeid(Wall)){
            if (direction == "Right") {
                this->moveBy(-25, 0);
            }
            else if (direction == "Left") {
                this->moveBy(25, 0);
            }
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

void Player::stand() {
    if(!groundContact){
        this->fall();
    }
}

void Player::run() {

    if(groundContact) {
        if (direction == "Right") {
            this->moveBy(10, 0);
            if(wallContact || this->x()-10 > 1100){
                this->moveBy(-25, 0);
            }
        } else if (direction == "Left") {
            this->moveBy(-10, 0);
            if (wallContact || this->x()-10 < 0) {
                this->moveBy(25, 0);
            }
        }
    } else {
        status = "Falling";
    }
}

void Player::jump() { //https://www.youtube.com/watch?v=c4b9lCfSDQM
    if(this->previousStatus=="Standing"){
        if (velocityY < 0 ){
            this->status = "Falling";
            return;
        } else {
            velocityX=0;
            this->moveBy(0, -velocityY * 10);
        }
    } else {
        if (velocityY < 0 || wallContact){
            this->status = "Falling";
            return;
        } else {
            if (direction == "Right") {
                this->moveBy(velocityX * 7, -velocityY * 10);
            } else if (direction == "Left") {
                this->moveBy(-velocityX * 10, -velocityY * 10);
            }
        }
    }
    velocityY = velocityY + gravity*0.15;
}

void Player::fall() {
    if(wallContact){
        if(this->pos().y()>=300){
            if(this->direction=="Right"){
                this->direction="Left";
            } else if(this->direction=="Left"){
                this->direction="Right";
            }
        } else {
            velocityX = 0;
        }
    }

    if(this->direction=="Right"){

        this->moveBy(velocityX*5,velocityY*5);
    } else if(this->direction=="Left"){
        this->moveBy(-velocityX*5,velocityY*5);
    }
    velocityY = velocityY - gravity * 0.15;

    if(this->pos().y()>=300){
        this->status = "Standing";
        this->setVelocity();
        return;
    }
}
