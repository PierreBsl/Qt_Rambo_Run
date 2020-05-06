#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QObject>
#include <QTime>
#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^
#include <QFile>       // Pour utiliser le fichier
#include <QString>     // Stocke le contenu du fichier
#include <QTextStream> // Flux sortant du fichier

extern MainScene * mainScene;

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    // init seed for random generation
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    MainWindow mainWindow;
//    mainWindow.show();

    return application.exec();
}
