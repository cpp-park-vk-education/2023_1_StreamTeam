#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SyncView");

    setAttribute(Qt::WA_QuitOnClose, true);
}

MainWindow::~MainWindow()
{
    delete ui;
    QApplication::quit();
}

void MainWindow::setCurrentUser(std::shared_ptr<User> ptr)
{
    login_user = ptr;
    ui->menuUser_Name->setTitle(QApplication::translate("MainWindow", login_user->GetName().c_str(), nullptr));
    ui->statusbar->showMessage("Login Success!");
}

std::shared_ptr<User> MainWindow::getCurrentUser()
{
    return login_user;
}

void MainWindow::quitApp()
{
    QApplication::closeAllWindows();
    QApplication::exit();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::closeAllWindows();
    // что то еще добавить
}


void MainWindow::on_actionLog_out_triggered()
{
    ui->menuUser_Name->setTitle(QApplication::translate("MainWindow", "User.Name", nullptr));
    login_user.reset();
    if (player)
        delete player;
    player = nullptr;
    AuthWindow authWindow(this, this);
    authWindow.setModal(true);
    authWindow.exec();
}

void MainWindow::on_pushButton_clicked()
{
    if (player)
        delete player;
    player = new PlayerWindow(this);
    player->show();
}

