#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class gameOver: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    gameOver(QGraphicsItem * parent=0);

    void display();
public slots:
    void setMute();
};

#endif // GAMEOVER_H
