#include "MainScene.h"
#include "Utils.h"
#include <QHBoxLayout>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QFont>
#include <QVector>
#include <QDebug>

extern MainScene* mainScene;

Player * player;
Score * score;
Health * health;
QTimer * timer_chrono;
gameOver * gameover;
QMediaPlayer * gameOverSound;
QMediaPlayer * endGameSound;
EndGame * endgame;
Monster * monster;

MainScene::MainScene() {

    this->background.load(":/img/panorama1.jpg");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->timer = new QTimer(this);

    QPushButton * startGameButton = new QPushButton("START GAME");
    startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
    startGameButton->setFixedSize(200, 35);
    startGameButton->move(0,-36);
    this->addWidget(startGameButton);

    connect(startGameButton, SIGNAL(clicked()), this, SLOT(startGame()));

    player = new Player("Heroe", ":/img/test.png");
    player->setPos(0,300);
    this->addItem(player);

}

void MainScene::startGame()
{
    //Game
    if(!timer->isActive()){

        //build end game door
        endgame = new EndGame();
        endgame->setPos(1100, 300);
        this->addItem(endgame);

        setGameOn(true);
        score = new Score();
        this->addItem(score);
        health = new Health();
        health->setPos(health->x(),health->y()+25);
        this->addItem(health);
        gameover = new gameOver();
        gameover->setPos(gameover->x()+450, gameover->y());

        timer->start(30);

        connect(timer, SIGNAL(timeout()), this, SLOT(update()));

        restartGameButton = new QPushButton("CLEAR GAME");
        restartGameButton->setObjectName(QString::fromUtf8("restartGameButton"));
        restartGameButton->setFixedSize(200, 35);
        restartGameButton->move(210,-36);
        this->addWidget(restartGameButton);

        connect(restartGameButton, SIGNAL(clicked()), this, SLOT(clearGame()));

        pauseGameButton  = new QPushButton("PAUSE GAME");
        pauseGameButton->setFixedSize(100, 35);
        pauseGameButton->move(770,-36);
        this->addWidget(pauseGameButton);

        resumeGameButton  = new QPushButton("RESUME GAME");
        resumeGameButton->setFixedSize(100, 35);
        resumeGameButton->move(880,-36);
        this->addWidget(resumeGameButton);

        chronoLCD = new QLCDNumber();
        chronoLCD->setFixedSize(100, 35);
        chronoLCD->move(990,-36);

        this->addWidget(chronoLCD);

        bestChronoLCD = new QLCDNumber();
        bestChronoLCD->setFixedSize(100, 35);
        bestChronoLCD->move(1100,-36);

        this->addWidget(bestChronoLCD);

        // Create Chrono and Game Dynamic

        timer_chrono = new QTimer;

        resetCount(); //Count Variable
        connect( timer_chrono, SIGNAL(timeout()), this, SLOT(onTimer_Tick()));
        connect( pauseGameButton, SIGNAL(clicked()), this, SLOT(pauseGame()));
        connect( resumeGameButton, SIGNAL(clicked()), this, SLOT(resumeGame()));

        //build floor
        int x_position = 0;
        for (int i=0; i<7; i++){
            floor = new Floor();
            floor->setPos(x_position,400);
            this->addItem(floor);
            x_position += 200;
        }

        //build wall
        int tmp =  Utils::randInt(200, 1000);
        wall = new Wall();
        wall->setPos(tmp, 250);
        this->addItem(wall);

        //build void
        int t = 0;
        if(tmp+400>800){
            t = tmp-400;
        }else{
            t = tmp+400;
        }
        vide = new Void();
        vide->setPos(t, 399);
        this->addItem(vide);

        //spawn monster
        monster = new Monster();
        this->addItem(monster);

        //spawn player
        if(player){removeItem(player);}
        player = new Player("Heroe", ":/img/test.png");
        player->setPos(0,300);
        this->addItem(player);

        //add bullet sound
        bulletsound = new QMediaPlayer();
        bulletsound->setMedia(QUrl("qrc:/sounds/sounds/fun.mp3"));

        //add game over sound
        gameOverSound = new QMediaPlayer();
        gameOverSound->setMedia(QUrl("qrc:/sounds/sounds/gameover.wav"));

        //add game over sound
        endGameSound = new QMediaPlayer();
        endGameSound->setMedia(QUrl("qrc:/sounds/sounds/applaudissements.wav"));

        //play backgroud music
        QMediaPlayer * music = new QMediaPlayer();
        music->setMedia(QUrl("qrc:/sounds/sounds/epic.wav"));
        music->play();
        connect( pauseGameButton, SIGNAL(clicked()), music , SLOT(pause()));
        connect( resumeGameButton, SIGNAL(clicked()), music, SLOT(play()));
        connect( restartGameButton, SIGNAL(clicked()), music, SLOT(stop()));
        connect( restartGameButton, SIGNAL(clicked()), endGameSound, SLOT(stop()));

        timer_chrono -> start(1000); // 1000 ms

        bestChronoLCD -> display(bestTime);
    }
}

void MainScene::clearGame()
{
    timer->stop();
    timer_chrono->stop();

    setGameOn(false);

    if(gameover){removeItem(gameover);}
    if(score){removeItem(score);}
    if(health){removeItem(health);}
    if(endgame){removeItem(endgame);}
    if(wall){removeItem(wall);}
    if(vide){removeItem(vide);}

    if(countTimer<bestTime){
        bestTime = countTimer;
    }
    resetCount();
    chronoLCD -> display(countTimer);
    bestChronoLCD -> display(bestTime);
}

void MainScene::pauseGame(){
    timer_chrono->stop();
}

void MainScene::resumeGame(){
    timer_chrono->start();
}

void MainScene::resetCount()
{
    countTimer=0;
}

void MainScene::updateCount()
{
    countTimer++;
}

void MainScene::setGameOn(bool value)
{
    gameOn = value;
}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::update() {

    player->startPlaying();

    // view update
    QGraphicsView * view = this->views().at(0);
    view->centerOn(player);
}

void MainScene::onTimer_Tick()
{
    updateCount();
    chronoLCD -> display(countTimer);
}

MainScene::~MainScene() {

    delete this->timer;
    delete player;

}

void MainScene::keyPressEvent(QKeyEvent *event)
{
    QPointF pos = player->pos();

    if(event->key() == Qt::Key_Up){
        if (pos.y() > 0){
            player->setPos(player->x(), player->y()-15);
        }
    }
    if(event->key() == Qt::Key_Down){
        if (pos.y() < 300){
            player->setPos(player->x(), player->y()+15);
        }
    }
    else if(event->key() == Qt::Key_Left){
        if (pos.x() > 0){
            player->setPos(player->x()-15, player->y());
        }
    }
    else if(event->key() == Qt::Key_Right){
        if (pos.x() < 1100){
            player->setPos(player->x()+15,player-> y());
        }
    }
    else if(event->key() == Qt::Key_Space){

        //create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(player->x()+100,player->y()+40);
        this->addItem(bullet);

        //play bulletsound
        if (bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}
