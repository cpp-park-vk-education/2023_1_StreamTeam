#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <memory>
#include <vector>
#include <queue>

#include "playerwindow.h"
#include "user.hpp"
#include "room.hpp"
#include "message.hpp"


Q_DECLARE_METATYPE(Message)
Q_DECLARE_METATYPE(std::shared_ptr<Message>)

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

    std::shared_ptr<User> getCurrentUser();

    void AddRoom(std::shared_ptr<Room>);

    void addMessage(std::shared_ptr<Message>);

    void clearRoomList();

    void clearCurrentRoom();

    void clearMessages();

private slots:

    void loadCurrentRoom();

    void loadMessages();

    void loadMembers();

    void loadRoomList();

    void addLastMessage();

    void showErrorMessage(const QString& title, const QString& message);

    void quitApp();

    void on_actionLog_out_triggered();

    void on_pushButtonPlayer_clicked();

    void slotSetCurrentRoom();

    void on_actionQuit_triggered();

    void on_pushButton_send_clicked();

    void on_pushButton_AddMember_clicked();

    void on_pushButton_3_clicked();

    void createPlayer(const std::string& ip_addr);

private:
    Ui::MainWindow *ui;
    //PlayerWindow* player;

    // Memory
    std::shared_ptr<User> login_user;
    std::shared_ptr<Room> current_room;
    std::vector<std::shared_ptr<Room>> user_rooms;
    std::vector<std::shared_ptr<Message>> current_room_messages;
    std::vector<std::shared_ptr<User>> current_room_members;

};
#endif // MAINWINDOW_H
