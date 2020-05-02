#ifndef MYSCENE_H
#define MYSCENE_H
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "health.h"
#include "wall.h"
#include "floor.h"
#include "monster.h"
#include "void.h"
#include "gameover.h"
#include "endgame.h"
#include "plateform.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include <QPainter>
#include <QRectF>
#include <QSlider>
#include <QPushButton>
#include <QLCDNumber>
#include <QGraphicsPixmapItem>

extern Player * player;

class MainScene : public QGraphicsScene, public QGraphicsPixmapItem {

    Q_OBJECT

private :

    QPixmap background;

    QMediaPlayer * bulletsound;

    QPushButton * pauseGameButton;
    QPushButton * resumeGameButton;
    QPushButton * restartGameButton;
    QPushButton * quitGameButton;

    QPushButton * m_dialogButton;

    QLCDNumber * chronoLCD;
    QLCDNumber * bestChronoLCD;

    QSlider * volume_slider;
    QGraphicsTextItem * volume_text;
    QGraphicsTextItem * score_text;
    QGraphicsTextItem * bestScore_text;

    QTimer * timerMonster;

    int nbMonster=0;

    int countTimer;
    int bestTime=100;
    bool gameOn;

    Floor * floor;
    void showGameOverGraphics();
    void hideGameOverGraphics();

private slots:

    void quit();
    void pauseGame();
    void resumeGame();

public:

    void startGame();
    void resetCount();
    void updateCount();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    bool getGameOn() const;
    void setGameOn(bool value);

    int getCountTimer();

    MainScene();
    void drawBackground(QPainter* painter, const QRectF& rect);
    virtual ~MainScene();

    QTimer * timer;
    QGraphicsPixmapItem * gameOverPix;

public slots :
    void clearGame();
    void update();
    void onTimer_Tick();
    void spawnMonsters();

    void spawnPlayerTommyGun();
    void spawnPlayerGrenade();
    void spawnPlayerSniper();
    void spawnPlayerShotgun();


};

#endif // MYSCENE_H
