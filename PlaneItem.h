#ifndef PLANE_H
#define PLANE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMediaPlayer>


#include "Utils.h"


class PlaneItem : public QGraphicsPixmapItem {


private :
    QString description;
    int speed;
    QMediaPlayer * bulletsound;

public slots:
    void spawn();
public:

    PlaneItem(QString description, QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName)), description(description) {
        bulletsound = new QMediaPlayer();
        bulletsound->setMedia(QUrl("qrc:/sounds/sounds/fun.mp3"));
    }

    void move();

    void keyPressEvent(QKeyEvent * event);

    int getSpeed() const { return speed; }
    const QString &getDescription() const { return this->description; }

    void setDescription(const QString &description) { this->description = description; }
    void setSpeed(int speed) { this->speed = speed; }


};

#endif // PLANE_H
