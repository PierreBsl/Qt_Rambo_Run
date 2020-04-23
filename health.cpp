#include "health.h"
#include "gameover.h"
#include <QFont>

extern gameOver * gameover;

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // initialize the score to 0
    health = 100;

    //draw the text
    setPlainText(QString("Health : ") + QString::number(health)); // Health : 0
    setDefaultTextColor(Qt::red);
    setFont(QFont("Consolas", 16));

}

void Health::decrease()
{
    health--;
    if(getHealth() == 0){
        gameover->display();
    }
    setPlainText(QString("Health : ") + QString::number(health)); // Health : updated

}

int Health::getHealth()
{
    return health;
}

