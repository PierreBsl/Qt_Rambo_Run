#include "MainScene.h"
#include "Utils.h"
#include <QApplication>
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
#include <QInputDialog>
#include <QMessageBox>
#include <iostream>
#include <QDebug>

extern MainScene* mainScene;
extern QString pseudo;

Player * player;
Score * score;
Health * health;
QTimer * timer_chrono;
gameOver * gameover;
QMediaPlayer * gameOverSound;
QMediaPlayer * endGameSound;
EndGame * endgame;
Monster * monster;
Wall * wall;
Wall * wall1;
Void * vide;
Plateform * plateform;

MainScene::MainScene() {

    this->background.load(":/img/panorama.jpg");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->timer = new QTimer(this);    

    player = new Player(pseudo, ":/img/test.png");
    player->setPos(0,350);
    this->addItem(player);
}

void MainScene::startGame()
{
    //Game
    if(!timer->isActive()){

        //build end game door
        endgame = new EndGame();
        endgame->setPos(1200, 350);
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

        quitGameButton = new QPushButton("QUIT GAME");
        quitGameButton->setObjectName(QString::fromUtf8("quitGameButton"));
        quitGameButton->setFixedSize(200, 35);
        quitGameButton->move(420,-36);
        this->addWidget(quitGameButton);

        connect(quitGameButton, SIGNAL(clicked()), this, SLOT(quit()));

        pauseGameButton  = new QPushButton("PAUSE GAME");
        pauseGameButton->setFixedSize(100, 35);
        pauseGameButton->move(870,-36);
        this->addWidget(pauseGameButton);

        resumeGameButton  = new QPushButton("RESUME GAME");
        resumeGameButton->setFixedSize(100, 35);
        resumeGameButton->move(980,-36);
        this->addWidget(resumeGameButton);

        chronoLCD = new QLCDNumber();
        chronoLCD->setFixedSize(100, 35);
        chronoLCD->move(1090,-36);

        this->addWidget(chronoLCD);

        bestChronoLCD = new QLCDNumber();
        bestChronoLCD->setFixedSize(100, 35);
        bestChronoLCD->move(1200,-36);

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
            floor->setPos(x_position,449);
            this->addItem(floor);
            x_position += 200;
        }

        //build wall
        int tmp =  Utils::randInt(200, 1100);
        if (tmp >=900 || tmp <= 450){
            wall1 = new Wall();
            wall1->setPos(tmp-700, 300);
            this->addItem(wall1);
        }
        wall = new Wall();
        wall->setPos(tmp, 300);
        this->addItem(wall);

        //build void
        int t = 0;
        if(tmp+450>1000){
            t = tmp-450;
        }else{
            t = tmp+450;
        }
        vide = new Void();
        vide->setPos(t, 449);
        this->addItem(vide);

        plateform = new Plateform(":/img/plateform.png");
        plateform->setPos(t,449);
        this->addItem(plateform);


        //spawn monster
        monster = new Monster();
        this->addItem(monster);

        //spawn player
        if(player){removeItem(player);}
        player = new Player(pseudo, ":/img/test.png");
        player->setPos(0,350);
        this->addItem(player);

        //add bullet sound
        bulletsound = new QMediaPlayer();
        bulletsound->setMedia(QUrl("qrc:/sounds/sounds/fun.mp3"));

        //add game over sound
        gameOverSound = new QMediaPlayer();
        gameOverSound->setMedia(QUrl("qrc:/sounds/sounds/gameover.wav"));

        //add end game sound
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

void MainScene::quit(){

    QApplication::quit();
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
    if(wall1){removeItem(wall1);}
    if(vide){removeItem(vide);}


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

    if (player->getPosition() != "Jumping") {
        player->setPreviousStatus(player->getPosition());
    }

    player->move();
    player->collisions();
    plateform->move();

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

    if (player->getPosition() == "Waiting" || player->getPosition() == "Running") {

        if(event->key() == Qt::Key_Up){
            if (event->isAutoRepeat()) {
                return;
            }
            std::string previousStatus = player->getPosition();
            player->setPosition("Jumping", previousStatus);
        }
        else if(event->key() == Qt::Key_Left){
            player->setPosition("Running");
            player->setDirection("Left");

        }
        else if(event->key() == Qt::Key_Right){
            player->setPosition("Running");
            player->setDirection("Right");

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
}

void MainScene::keyReleaseEvent(QKeyEvent *event) {

    if(player->getPosition() != "Jumping" && player->getPosition() != "Falling") {
        if (event->isAutoRepeat()) {
            return;
        }
        player->setPosition("Waiting");
    }
}
