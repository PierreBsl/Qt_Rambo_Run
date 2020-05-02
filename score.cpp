#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    // initialize the score to 0
    score = 0;

    //draw the text
    setPlainText(QString("Enemies killed : ") + QString::number(score)); // Score : 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Consolas", 16));

}

void Score::increase()
{
    score++;
    setPlainText(QString("Enemies killed : ") + QString::number(score)); // Score : updated
}

int Score::getScore()
{
    return score;
}
