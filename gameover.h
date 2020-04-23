#ifndef GAMEOVER_H
#define GAMEOVER_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class gameOver: public QGraphicsPixmapItem
{
public:
    gameOver();

    void display();
};

#endif // GAMEOVER_H
