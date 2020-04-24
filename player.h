#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QGraphicsItemAnimation>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>
#include <QVector2D>
#include <QGraphicsItem>
#include <QPropertyAnimation>

#include "Utils.h"


class Player: public QGraphicsPixmapItem
{

public slots:

    void collisions();

public:

    QGraphicsPixmapItem * gameOverPix;

    Player(QString description, QString imageFileName);

    const QString &getDescription() const {return this->description;}
    void setDescription(const QString &description) {this->description = description;}

    bool onGround = false;

    void setDirection(std::string);
    void setVelocity();
    void setPreviousStatus(std::string);

    void move();

    void run();
    void jump();
    void fall();
    void stand();

    void setStatus(std::string,std::string = "");
    std::string getStatus();
    void setwallContact();
    void setgroundContact();

    bool wallContact;
    bool groundContact;


private :

    std::string status;
    std::string previousStatus;
    std::string direction;
    float velocityX;
    float velocityY;
    float gravity;

    QString description;
    qreal groundPosition;

};

#endif // PLAYER_H
