#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <memory>

#include "user.hpp"
#include "playerwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setCurrentUser(std::shared_ptr<User>);

    std::shared_ptr<User> getCurrentUser();

    void quitApp();

private slots:
    void on_actionQuit_triggered();

    void on_actionLog_out_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    PlayerWindow *player;
    std::shared_ptr<User> login_user;

};
#endif // MAINWINDOW_H
