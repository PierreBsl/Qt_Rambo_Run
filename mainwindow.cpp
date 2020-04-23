#include <QHBoxLayout>
#include <QMainWindow>
#include <QTextEdit>
#include <QTimer>
#include <QFont>
#include <QPushButton>
#include <QImage>
#include "mainwindow.h"

MainScene* mainScene;

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
    this->setFixedSize(1200,500);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
