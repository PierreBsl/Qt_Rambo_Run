#include "endgame.h"

extern Player * player;
extern MainScene * mainScene;
extern Score * score;
extern Health * health;

EndGame::EndGame(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/img/porte.jpg"));

}

void EndGame::endScreen()
{
    setPixmap(QPixmap(":/img/Win.png"));
    setPos(player->pos().x()-500,player->pos().y()-225);

    mainScene->writeScore();
}
