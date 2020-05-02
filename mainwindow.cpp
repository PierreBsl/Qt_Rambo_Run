#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QTimer>
#include <QFont>
#include <QPushButton>
#include <QImage>
#include <QInputDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QtWidgets>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QRadioButton>
#include "mainwindow.h"

extern QTimer * timer_chrono;
MainScene* mainScene;
QString pseudo;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    mainScene = new MainScene();

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    
    QGraphicsView* playerView = new QGraphicsView();
    playerView->setScene(mainScene);
    playerView->resize(300, 300);
    playerView->setWindowTitle(player->getDescription());
    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->show();
    
    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    
    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->setFixedSize(1300,600);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    if(!timer_chrono){
        QPushButton * startGameButton = new QPushButton("START GAME");
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
        startGameButton->setFixedSize(150, 35);
        startGameButton->move(0,-36);
        mainScene->addWidget(startGameButton);
        
        QObject::connect(startGameButton, SIGNAL(clicked()), this, SLOT(username()));
    }else {
        QMessageBox::information(this, "Information", "Vous avez déjà saisi votre pseudo ");
        
    }
    
}
void MainWindow::username()
{
    pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString());
    if (!pseudo.isEmpty())
    {
        QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", Bienvenue dans Army Run ");

        QWidget *window = new QWidget;
        window->resize(290, 375);
        QGroupBox *groupbox = new QGroupBox("Choose a weapon ", window);

        QPushButton *tommy_gun = new QPushButton();
        tommy_gun->setIcon(QPixmap(":/img/mitraillete.png"));
        tommy_gun->setIconSize(QPixmap(":/img/mitraillete.png").size());
        connect(tommy_gun, SIGNAL(clicked()), mainScene, SLOT(spawnPlayerTommyGun()));

        QPushButton *grenade = new QPushButton();
        grenade->setIcon(QPixmap(":/img/grenade.png"));
        grenade->setIconSize(QPixmap(":/img/grenade.png").size());
        connect(grenade, SIGNAL(clicked()), mainScene, SLOT(spawnPlayerGrenade()));


        QPushButton *sniper = new QPushButton();
        sniper->setIcon(QPixmap(":/img/sniper.png"));
        sniper->setIconSize(QPixmap(":/img/sniper.png").size());
        connect(sniper, SIGNAL(clicked()), mainScene, SLOT(spawnPlayerSniper()));

        QPushButton *shotgun = new QPushButton();
        shotgun->setIcon(QPixmap(":/img/pompe.png"));
        shotgun->setIconSize(QPixmap(":/img/pompe.png").size());
        connect(shotgun, SIGNAL(clicked()), mainScene, SLOT(spawnPlayerShotgun()));

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(tommy_gun);
        layout->addWidget(grenade);
        layout->addWidget(sniper);
        layout->addWidget(shotgun);

        groupbox->setLayout(layout);
        window->show();
    }
    else
    {
        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom.");
    }
    
}
