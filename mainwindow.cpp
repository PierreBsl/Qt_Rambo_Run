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
#include <QGraphicsView>
#include <QLabel>
#include <QFile>
#include <QTextEdit>   // Nous allons tout de même afficher le contenu du fichier ^^
#include <QFile>       // Pour utiliser le fichier
#include <QString>     // Stocke le contenu du fichier
#include <QTextStream> // Flux sortant du fichier
#include <QRadioButton>
#include "mainwindow.h"

extern QTimer * timer_chrono;
extern QMediaPlayer * gameOverSound;
extern QMediaPlayer * endGameSound;
extern QMediaPlayer * music;
extern QMediaPlayer * bulletsound;
extern bool gameOn;
extern Score * score;
extern Health * health;
bool firstGame;
MainScene* mainScene;
QGraphicsView * playerView;
QWidget *fenetre;
QWidget *gunsChoice;
QString pseudo;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    firstGame = true;

    mainScene = new MainScene();

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    
    playerView = new QGraphicsView();
    playerView->setScene(mainScene);
    playerView->resize(900, 500);
    playerView->setWindowTitle("Player View");
    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->show();
    

    mainView = new QGraphicsView();
    mainView->setScene(mainScene);
    
    this->setCentralWidget(mainView);
    this->setWindowTitle("Main view");
    this->setFixedSize(3000,600);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    fenetre = new QWidget;
    fenetre->setWindowTitle("Menu");

    // 1 : Créer le QTabWidget
    QTabWidget *onglets = new QTabWidget(fenetre);
    onglets->setGeometry(30, 20, 240, 160);

    // 2 : Créer les pages, en utilisant un widget parent pour contenir chacune des pages
    QWidget *page1 = new QWidget;
    QWidget *page2 = new QWidget;
    QWidget *page3 = new QWidget; // Comme un QLabel est aussi un QWidget (il en hérite), on peut aussi s'en servir de page

    // 3 : Créer le contenu des pages de widgets

    // Page 1
    QPushButton *startGameButton = new QPushButton("START GAME");
    QPushButton *quitGameButton = new QPushButton("QUIT GAME");

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(startGameButton);
    vbox1->addWidget(quitGameButton);

    page1->setLayout(vbox1);

    // Page 2

    QTextEdit * volumeMusic = new QTextEdit();
    QTextEdit * volumeSlider = new QTextEdit("Effects Volume");
    volume_music = new QSlider(Qt::Horizontal);
    volume_music->setValue(50);
    volume_slider = new QSlider(Qt::Horizontal);
    volume_slider->setValue(50);

    resumeGameButton = new QPushButton("RESUME GAME");

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(volumeMusic);
    vbox2->addWidget(volume_music);
    vbox2->addWidget(volumeSlider);
    vbox2->addWidget(volume_slider);
    vbox2->addWidget(resumeGameButton);

    page2->setLayout(vbox2);

    // Page 3

    QTextEdit * textZone = new QTextEdit();
    textZone->setGeometry(100,100,400,200);
    textZone->setReadOnly(true);

    QString text;

    QFile fichier(":/scores.txt");

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd())
            text += flux.readLine() + '\n';
        text.resize(text.size()-1); // Élimine le '\n' en trop
        fichier.close();
    }

    else text = "Impossible to reach file destination";

    textZone->setText(text);
    textZone->show();

    clearScoresButton  = new QPushButton("CLEAR SCORES");

    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(textZone);
    vbox3->addWidget(resumeGameButton);
    vbox3->addWidget(clearScoresButton);
    page3->setLayout(vbox3);

    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(page1, "Username");
    onglets->addTab(page2, "Settings");
    onglets->addTab(page3, "Scores");

    fenetre->show();

    //play backgroud music
    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sounds/epic.wav"));
    music->play();

    //add bullet sound
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/sounds/fun.mp3"));

    //add game over sound
    gameOverSound = new QMediaPlayer();
    gameOverSound->setMedia(QUrl("qrc:/sounds/sounds/gameover.wav"));

    //add end game sound
    endGameSound = new QMediaPlayer();
    endGameSound->setMedia(QUrl("qrc:/sounds/sounds/applaudissements.wav"));

    connect(startGameButton, SIGNAL(clicked()), this, SLOT(username()));

    connect(quitGameButton, SIGNAL(clicked()), mainScene, SLOT(quit()));

    connect(resumeGameButton, SIGNAL(clicked()), mainScene, SLOT(resumeGame()));

    connect(clearScoresButton, SIGNAL(clicked()), mainScene, SLOT(eraseText()));

    connect(volume_music, SIGNAL(valueChanged(int)), music, SLOT(setVolume(int))) ;
    connect(volume_slider, SIGNAL(valueChanged(int)), bulletsound, SLOT(setVolume(int))) ;
    connect(volume_slider, SIGNAL(valueChanged(int)), gameOverSound, SLOT(setVolume(int))) ;
    connect(volume_slider, SIGNAL(valueChanged(int)), endGameSound, SLOT(setVolume(int))) ;

}
void MainWindow::username()
{
    fenetre->hide();
    pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString());
    if (!pseudo.isEmpty())
    {
        gunsChoice = new QWidget;
        gunsChoice->resize(290, 375);
        QGroupBox *groupbox = new QGroupBox("Choose a weapon " + pseudo, gunsChoice);

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
        gunsChoice->show();

    }
    else
    {
        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom.");
    }
}
