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
#include <QTime>
#include <QVBoxLayout>
#include <QPainter>
#include <QRectF>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>
#include <QGraphicsPixmapItem>

extern Player * player;

class MainScene : public QGraphicsScene, public QGraphicsPixmapItem {

    Q_OBJECT

private :

    QPixmap background;
    QGraphicsPixmapItem * gameOverPix;

    QPushButton * m_dialogButton;

    QTimer * timer;

    QTimer * timerMonster;

    int nbMonster=0;

    int chrono;

    QString texte ;

    Floor * floor;
    Wall * wall1;
    Wall * wall2;
    Wall * wall3;
    Wall * wall4;
    Wall * wall5;

    Void * vide;
    Void * vide1;
    Void * vide2;

    Plateform * plateform;
    Plateform * plateform1;
    Plateform * plateform2;

    Monster * monster;
    Monster * monster1;
    Monster * monster2;
    Monster * monster3;

    void showGameOverGraphics();
    void hideGameOverGraphics();

private slots:

    void quit();
    void pauseGame();
    void resumeGame();

public:

    void startGame();

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);

    bool getGameOn() const;
    void setGameOn(bool value);

    MainScene();
    void drawBackground(QPainter* painter, const QRectF& rect);
    virtual ~MainScene();

    void writeScore();

    bool collidingPlateform();

public slots :

    void clearGame();
    void update();

    void spawnPlayerTommyGun();
    void spawnPlayerGrenade();
    void spawnPlayerSniper();
    void spawnPlayerShotgun();

    void eraseText();

};

#endif // MYSCENE_H
