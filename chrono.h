#ifndef CHRONO_H
#define CHRONO_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPropertyAnimation>

#include "Utils.h"

class Chrono
{
public:
    Chrono();

    void resetCount();
    void updateCount();

public slots:
    void onTimer_Tick();
    void onButton_Start();
    void onButton_Reset();

private:
    QPushButton *m_bout_start;
    QPushButton *m_bout_stop;
    QPushButton *m_bout_reset;

    QGridLayout *m_layout;

    QLCDNumber *m_lcd;

    QTimer *timer_chrono;

    int countTimer;
};

#endif // CHRONO_H
