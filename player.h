#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>

#include "Utils.h"


class Player: public QGraphicsPixmapItem
{

public slots:

    void startPlaying();
    void fallToGroundIfNecessary();

public:

    QGraphicsPixmapItem * gameOverPix;

    Player(QString description, QString imageFileName);

    const QString &getDescription() const { return this->description; }

    void setDescription(const QString &description) { this->description = description; }

public slots:

private :


    QString description;
    qreal groundPosition;


};

#endif // PLAYER_H
