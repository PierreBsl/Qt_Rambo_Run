#ifndef MYSCENE_H
#define MYSCENE_H
#include "chrono.h"
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

    MainScene();
    void drawBackground(QPainter* painter, const QRectF& rect);
    const Player * getPlayer(){return player;}
    virtual ~MainScene();

    QTimer * timer;
    QGraphicsPixmapItem * gameOverPix;

public slots :
    void clearGame();
    void update();
    void onTimer_Tick();

};

#endif // MYSCENE_H
