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
    QGraphicsView* mainView;
    QPushButton * pauseGameButton;
    QPushButton * resumeGameButton;
    QPushButton * clearScoresButton;

    QSlider * volume_slider;
    QSlider * volume_music;

public:

    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow() {};

public slots:
    void username();
};

#endif // MAINWINDOW_H
