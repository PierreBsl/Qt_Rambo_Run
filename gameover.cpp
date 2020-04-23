#include "gameover.h"
#include "player.h"
#include "bullet.h"
#include "monster.h"
#include "mainwindow.h"
#include "MainScene.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

extern MainScene* mainScene;
extern Player * player;
extern Health * health;
extern Monster * monster;
extern QTimer * timer_chrono;
extern gameOver * gameover;
extern QMediaPlayer * gameOverSound;
extern QMediaPlayer * endGameSound;
extern EndGame * endgame;

gameOver::gameOver()
{
    setPixmap(QPixmap(":/img/game_over.png"));
}
void gameOver::display(){

    if (gameOverSound->state() == QMediaPlayer::PlayingState){
        gameOverSound->setPosition(0);
    }
    else if (gameOverSound->state() == QMediaPlayer::StoppedState){
        gameOverSound->play();
    }
    mainScene->addItem(gameover);
    mainScene->removeItem(player);
    timer_chrono->stop();
}
