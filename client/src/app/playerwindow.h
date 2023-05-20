#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDialog>
#include "session.hpp"
#include "mainwindow.h"
//#include "ui_playerwindow.h"
//#include "ui_mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtNetwork/QNetworkRequest>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QString>


//
//QT_BEGIN_NAMESPACE
//namespace Ui { class PlayerWindow; }
//QT_END_NAMESPACE


class PlayerWindow : public QDialog
{
    Q_OBJECT

public:
    PlayerWindow(QWidget *parent): QDialog(parent)
    {
//        ui->setupUi(this);
        setWindowTitle("StreamTeam video streaming service");

        QVideoWidget* vw = new QVideoWidget(this);
        QMediaPlayer* player = new QMediaPlayer(this);

        QGridLayout* layout = new QGridLayout(this);
        layout->addWidget(vw, 0, 0, 1, 1);

//        QWidget* win = new QWidget(this);
//        win->setLayout(layout);
//        setCentralWidget(win);

        player->setVideoOutput(vw);
        const QUrl url1 = QUrl("rtsp://127.0.0.1:8554/stream1");
        const QNetworkRequest requestRtsp1(url1);

        player->setMedia(requestRtsp1);
        player->play();
    }

    ~PlayerWindow()
    {}

private:
    QString ip_address;
//    Ui::PlayerWindow *ui;
};

#endif // PLAYERWINDOW_H
