//#ifndef CHRONO_H
//#define CHRONO_H
//#include <QWidget>
//#include <QTimr>
//#include <QTime>
//#include <QLabel>
//#include <QPushButton>
//#include <QVBoxLayout>

//class Chrono : public QWidget {
//    Q_OBJECT
//    QTime startTime;
//    QTimer t;
//    QLabel * l;
//    QPushButton * startB, * stopB;
//public:
//        Chrono() {
//        QVBoxLayout * ly = new QVBoxLayout;
//        setLayout(ly);
//        ly->addWidget(l = new QLabel(this));
//        l->setText(QTime(0, 0).toString());
//        ly->addWidget(startB = new QPushButton("start", this));
//        ly->addWidget(stopB = new QPushButton("stop", this));
//        connect(&t, SIGNAL(timeout()), this, SLOT(updateTime()));
//        connect(startB, SIGNAL(clicked(bool)), this, SLOT(start()));
//        connect(stopB, SIGNAL(clicked(bool)), &t, SLOT(stop()));
//    }
//public slots:
//    void updateTime() { l->setText(QTime(0, 0).addMSecs(startTime.elapsed()).toString()); }
//    void start() {
//        l->setText(QTime(0, 0).toString());
//        startTime.restart();
//        t.start(1000);
//    }
//};

//#endif // CHRONO_H

