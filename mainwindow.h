#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MainScene.h"
#include "player.h"
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QVector>


class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    MainScene* mainScene;

    QVector<QGraphicsView*> playerViews;
    QGraphicsView* mainView;
    QPushButton * pauseGameButton;


private slots:
public:

    Health * health;

    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};



};

#endif // MAINWINDOW_H
