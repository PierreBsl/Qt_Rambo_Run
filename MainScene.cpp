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
#include <QMessageBox>
#include <iostream>
#include <QDebug>

#include <QTextStream>
#include <QInputDialog>
#include <QIODevice>
#include <QString>
#include <QFile>

extern MainScene* mainScene;
extern QString pseudo;
extern QWidget * fenetre;
extern QWidget * gunsChoice;
extern QGraphicsView * playerView;
extern bool firstGame;

Player * player;
Score * score;
Health * health;
gameOver * gameover;
QMediaPlayer * gameOverSound;
QMediaPlayer * endGameSound;
QMediaPlayer * music;
QMediaPlayer * bulletsound;
EndGame * endgame;
QTime * timer_chrono;
bool gameOn;

MainScene::MainScene() {

    this->background.load(":/img/panorama.jpg");
    this->setSceneRect(0, 0, background.width(), background.height());

    this->timer = new QTimer(this);
    this->timerMonster = new QTimer(this);
    timer_chrono = new QTime();
    player = new Player(pseudo, "", "");
    player->setPos(0,350);
    this->addItem(player);
}

void MainScene::startGame()
{
    //Game
    if(timer->isActive()){
        clearGame();
    }

    gameOn = true;
    firstGame = false;
    gunsChoice->hide();

    //build end game door
    endgame = new EndGame();
    endgame->setPos(2900, 350);
    this->addItem(endgame);

    setGameOn(true);
    score = new Score();
    this->addItem(score);

    health = new Health();
    this->addItem(health);

    gameover = new gameOver();

    timerMonster->start(40);
    timer->start(30);

    // Create Chrono and Game Dynamic

    timer_chrono = new QTime;

    //build wall
    wall1 = new Wall();
    wall1->setPos(200, 310);
    this->addItem(wall1);

    wall2 = new Wall();
    wall2->setPos(450, 310);
    this->addItem(wall2);

    wall3 = new Wall();
    wall3->setPos(1200, 310);
    this->addItem(wall3);

    wall4 = new Wall();
    wall4->setPos(1450, 310);
    this->addItem(wall4);

    wall5 = new Wall();
    wall5->setPos(2734, 310);
    this->addItem(wall5);

    //build floor
    int x_position = 0;
    for (int i=0; i<15; i++){
        floor = new Floor();
        floor->setPos(x_position,449);
        this->addItem(floor);
        x_position += 200;
    }

    //build void
    vide = new Void();
    vide->setPos(800, 449);
    this->addItem(vide);

    vide1 = new Void();
    vide1->setPos(1750, 449);
    this->addItem(vide1);

    vide2 = new Void();
    vide2->setPos(2250, 449);
    this->addItem(vide2);

    //build plateforms
    plateform = new Plateform();
    plateform->setPos(800,290);
    this->addItem(plateform);

    plateform1 = new Plateform();
    plateform1->setPos(1750,290);
    this->addItem(plateform1);

    plateform2 = new Plateform();
    plateform2->setPos(2250,290);
    this->addItem(plateform2);

    //spawn player
    this->addItem(player);

    //spawn monster
    monster = new Monster();
    monster->setPos(800,230);
    this->addItem(monster);

    monster1 = new Monster();
    monster1->setPos(1750,230);
    this->addItem(monster1);

    monster2 = new Monster();
    monster2->setPos(2250,230);
    this->addItem(monster2);

    monster3 = new Monster();
    monster3->setPos(2750, 390);
    this->addItem(monster3);

    //chronometer
    timer_chrono->start();

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    connect(timerMonster, SIGNAL(timeout()), monster, SLOT(move()));
    connect(timerMonster, SIGNAL(timeout()), monster1, SLOT(move()));
    connect(timerMonster, SIGNAL(timeout()), monster2, SLOT(move()));
    connect(timerMonster, SIGNAL(timeout()), monster3, SLOT(move()));

}

void MainScene::spawnPlayerTommyGun()
{
    if(player){removeItem(player);}

    player = new Player(pseudo, ":/img/mitaillette_right.png", ":/img/mitaillette_left.png");
    player->setPos(0,350);

    this->startGame();

}
void MainScene::spawnPlayerGrenade()
{
    if(player){removeItem(player);}

    player = new Player(pseudo, ":/img/grenade_right.png", ":/img/grenade_left.png");
    player->setPos(0,350);

    this->startGame();
}
void MainScene::spawnPlayerSniper()
{
    if(player){removeItem(player);}

    player = new Player(pseudo, ":/img/sniper_right.png", ":/img/sniper_left.png");
    player->setPos(0,350);

    this->startGame();
}
void MainScene::spawnPlayerShotgun()
{
    if(player){removeItem(player);}

    player = new Player(pseudo, ":/img/pompe_right.png", ":/img/pompe_left.png");
    player->setPos(0,350);

    this->startGame();
}

void MainScene::quit(){

    QApplication::quit();
}

void MainScene::clearGame()
{
    timer->stop();
    setGameOn(false);

    //delete old player
    if(player){removeItem(player);}
    if(gameover){removeItem(gameover);}
    if(endgame){removeItem(endgame);}
    delete endGameSound;
    delete gameOverSound;

    if(wall1){removeItem(wall1);}
    if(wall2){removeItem(wall2);}
    if(wall3){removeItem(wall3);}
    if(wall4){removeItem(wall4);}
    if(wall5){removeItem(wall5);}

    if(vide){removeItem(vide);}
    if(vide1){removeItem(vide1);}
    if(vide2){removeItem(vide2);}

    if(plateform){removeItem(plateform);}
    if(plateform1){removeItem(plateform);}
    if(plateform2){removeItem(plateform);}

    if(monster){removeItem(monster);}
    if(monster1){removeItem(monster1);}
    if(monster2){removeItem(monster2);}
    if(monster3){removeItem(monster3);}

}

void MainScene::pauseGame(){
    bulletsound->stop();
    endGameSound->stop();
    gameOverSound->stop();
}

void MainScene::resumeGame(){
    qDebug()<<"resume Game";
    fenetre->hide();
    music->play();
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

    texte = pseudo + ";" + QString::number(timer_chrono->elapsed() / 100000) + ":" + QString::number(timer_chrono->elapsed() / 1000) + ":" + QString::number(timer_chrono->elapsed() / 10 % 100) + "\n";

    score->setPos(player->x()-30, player->y()-50);
    health->setPos(player->x()-30, player->y()-30);

    gameover->setPos(player->x()-50,player->y()-200);

    if (player->getPosition() != "Jumping") {
        player->setPreviousStatus(player->getPosition());
    }
    QList<QGraphicsItem *>colliding_items = player->collidingItems();
    for(int i=0, n=colliding_items.size(); i<n; ++i){
        if(typeid(*(colliding_items[i])) == typeid(Plateform) && player->getPosition()=="Jumping"){
            qDebug()<<"plateform";
            player->setPosition("Waiting");
        }
        if(typeid(*(colliding_items[i])) == typeid(Plateform) && player->pos().y()+80>=290){
            player->setPosition("Falling");
        }

    }

    player->move();
    player->collisions();

    // view update
    QGraphicsView * view = this->views().at(0);
    view->centerOn(player);


    if(!collidingPlateform() && player->pos().y()<=349 && player->getPosition()!="Jumping" && player->getPosition()!="Falling"){
        player->setPosition("Falling");
    }

    if(player->collidesWithItem(endgame)){
        this->writeScore();
    }
}

void MainScene::writeScore(){

    QFile file("scores.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug()<<"oui";

        QTextStream flux(&file);
        flux << texte;
        file.write(texte.toLatin1(),texte.size());
        file.close();
    }
    else {qDebug()<<"erreur ouverture fichier";}
}

bool MainScene::collidingPlateform()
{
    QList<QGraphicsItem *>colliding_items2 = player->collidingItems();
    for(int i=0, n=colliding_items2.size(); i<n; ++i){
        if(typeid(*(colliding_items2[i])) == typeid(Plateform)){
            return true;
        }
    }
    return false;
}
void MainScene::eraseText(){
    QFile fichier(":/scores.txt");
    if(!fichier.remove()){
        QMessageBox::critical(NULL,"Erreur","Impossible de supprimer le fichier !");
    }
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
            if (player->getDirection()=="Right"){
                bullet->setPos(player->x()+100,player->y()+40);
            }
            if (player->getDirection()=="Left"){
                bullet->setPos(player->x(),player->y()+40);
            }
            this->addItem(bullet);

            //play bulletsound
            if (bulletsound->state() == QMediaPlayer::PlayingState){
                bulletsound->setPosition(0);
            }
            else if (bulletsound->state() == QMediaPlayer::StoppedState){
                bulletsound->play();
            }
        }
        else if(event->key() == Qt::Key_Escape){
            this->pauseGame();
            fenetre->show();
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
