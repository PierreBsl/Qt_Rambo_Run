#include "mainwindow.h"
#include "gameover.h"
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    // init seed for random generation
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
