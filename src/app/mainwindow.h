#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <memory>
#include <vector>

#include "localmemory.hpp"
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

    void Authenticate(std::shared_ptr<User>);

    void quitApp();

    std::shared_ptr<User> getCurrentUser();

    void loadRoomList();

    void AddRoom(std::shared_ptr<Room>);

    void clearRoomList();

    void loadCurrentRoom();

    void clearCurrentRoom();

    void loadMessages();

    void addMessage(Message);

    void clearMessages();

private slots:

    void on_actionLog_out_triggered();

    void on_pushButtonPlayer_clicked();

    void slotSetCurrentRoom();

    void on_actionQuit_triggered();

    void on_pushButton_send_clicked();

    void on_pushButton_AddMember_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    PlayerWindow *player;

    // Memory
    std::shared_ptr<User> login_user;
    std::shared_ptr<Room> current_room;
    std::vector<std::shared_ptr<Room>> user_rooms;
    std::vector<std::shared_ptr<Message>> current_room_messages;

};
#endif // MAINWINDOW_H
