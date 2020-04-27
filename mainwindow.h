#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainScene.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include "player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    QGraphicsView playerView;
    QGraphicsView* mainView;
    QPushButton * pauseGameButton;

public:

    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};

public slots:
    void username();
};

#endif // MAINWINDOW_H
