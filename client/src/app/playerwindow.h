#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDialog>
#include "session.hpp"
#include "mainwindow.h"
#include "ui_playerwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGridLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtNetwork/QNetworkRequest>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QString>


Q_DECLARE_METATYPE(std::string)

QT_BEGIN_NAMESPACE
namespace Ui { class PlayerWindow; }
QT_END_NAMESPACE


class PlayerWindow : public QDialog
{
    Q_OBJECT

public:
    PlayerWindow(QWidget *parent = nullptr, std::string ip_ = "");

    ~PlayerWindow();

private:
    QString ip_address;
    Ui::PlayerWindow *ui;
};

#endif // PLAYERWINDOW_H
