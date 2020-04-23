#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
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

    void startPlaying();

public:

    void jump();

    QGraphicsPixmapItem * gameOverPix;

    Player(QString description, QString imageFileName);

    const QString &getDescription() const { return this->description; }

    void setDescription(const QString &description) { this->description = description; }

private :

    QPointF position;
    QVector2D velocity;
    QVector2D gravity;
    QString description;
    qreal groundPosition;

    float previousTime;


};

#endif // PLAYER_H
