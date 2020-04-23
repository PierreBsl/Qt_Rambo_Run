#ifndef ENDGAME_H
#define ENDGAME_H
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "Utils.h"

class EndGame: public QGraphicsPixmapItem
{
public:
    EndGame(QGraphicsItem * parent=0);
    void endScreen();
};

#endif // ENDGAME_H
