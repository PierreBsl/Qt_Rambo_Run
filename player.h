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

    Player(QString, const QString&, const QString&);

    const QString &getDescription() const {return this->description;}
    void setDescription(const QString &description) {this->description = description;}

    bool onGround = false;

    void setDirection(std::string);
    std::string getDirection();
    void setVelocity();
    void setPreviousStatus(std::string);

    void move();

    void running();
    void jumping();
    void falling();
    void waiting();

    void setPosition(std::string,std::string = "");
    std::string getPosition();
    void setwallContact();
    void setgroundContact();

    QString imgRight;
    QString imgLeft;


private :

    std::string position;
    std::string previousStatus;
    std::string direction;
    std::string gun;
    float vitesseX;
    float vitesseY;
    float gravity;

    bool wallContact;
    bool plateformContact = false;
    bool groundContact;

    QString description;
    qreal groundPosition;

};

#endif // PLAYER_H
