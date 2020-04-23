#include "endgame.h"

EndGame::EndGame(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/img/porte.jpg"));

}

void EndGame::endScreen()
{
    setPixmap(QPixmap(":/img/Win.png"));
    setPos(this->x()-725,this->y()-250);
}
