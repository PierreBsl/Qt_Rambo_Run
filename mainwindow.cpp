#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QTimer>
#include <QFont>
#include <QPushButton>
#include <QImage>
#include <QInputDialog>
#include <QMessageBox>
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

    if(!(timer_chrono)){
        QPushButton * startGameButton = new QPushButton("START GAME");
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
        startGameButton->setFixedSize(200, 35);
        startGameButton->move(0,-36);
        mainScene->addWidget(startGameButton);

        QObject::connect(startGameButton, SIGNAL(clicked()), this, SLOT(username()));
    }else if (timer_chrono){
        QMessageBox::information(this, "Information", "Vous avez déjà saisi votre pseudo ");

    }

}
void MainWindow::username()
{
    bool ok = false;
    pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString(), &ok);
    if (ok && !pseudo.isEmpty())
    {
        QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", Bienvenue dans Army Run ");

        mainScene->startGame();
    }
    else
    {
        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom.");
    }

}
