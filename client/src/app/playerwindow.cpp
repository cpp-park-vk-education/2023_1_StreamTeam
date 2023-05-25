#include "playerwindow.h"
#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(QWidget *parent, std::string ip_) :
    QDialog(parent),
    ui(new Ui::PlayerWindow)
{
    ui->setupUi(this);
    setWindowTitle("StreamTeam video streaming service");

    QVideoWidget* vw = new QVideoWidget(this);
    QMediaPlayer* player = new QMediaPlayer(this);
    ui->layout_player->addWidget(vw);

    ip_address = QString::fromStdString(ip_.c_str());
    player->setVideoOutput(vw);
    const QUrl url1 = QUrl(ip_address);
    const QNetworkRequest requestRtsp1(url1);

    player->setMedia(requestRtsp1);
    player->play();
}

PlayerWindow::~PlayerWindow()
{
    delete ui;
}
