#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authwindow.h"
#include "createroomform.h"
#include "qdynamicbutton.h"

#include <QMessageBox>
#include <chrono>


void MainWindow::on_actionLog_out_triggered()
{
    ui->menuUser_Name->setTitle(QApplication::translate("MainWindow", "User.Name", nullptr));

    // Memory Free
    current_room.reset();
    login_user.reset();

    user_rooms.clear();
    user_rooms.shrink_to_fit();

    current_room_messages.clear();
    current_room_messages.shrink_to_fit();
    //

    clearRoomList();
    clearCurrentRoom();

    if (player)
        delete player;
    player = nullptr;

    AuthWindow authWindow(this, this);
    authWindow.setModal(true);
    authWindow.exec();
}

void MainWindow::on_pushButtonPlayer_clicked()
{
    if (player)
        delete player;
    player = new PlayerWindow(this);
    player->show();
}

void MainWindow::slotSetCurrentRoom()
{
    QDynamicButtonRoom *button = (QDynamicButtonRoom*) sender();

    current_room = button->getObjectPtr();
    loadCurrentRoom();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_send_clicked()
{
    if (ui->lineEditmessage->text() == "")
        return;
    std::string body = ui->lineEditmessage->text().toStdString();
    std::time_t t = std::time(0);
    std::string time = ctime(&t);
    time.resize(time.size()-1);
    Message message;
    message.SetAuthor(*login_user); message.SetPostTime(time); message.SetTextBody(body);
    current_room->AddMessage(message);
    ui->lineEditmessage->clear();
    addMessage(message);
    ui->listMessages->scrollToBottom();
}

void MainWindow::on_pushButton_AddMember_clicked()
{
    if(ui->lineEditAddMember->text() == "")
        return;
    int id = ui->lineEditAddMember->text().toInt();
    for (size_t i = 0; i< current_room->sizeofMembers(); ++i)
    {
        if (current_room->GetMember(i).GetId() == id)
        {
            ui->statusbar->showMessage("User is already in Room!");
            return;
        }
    }
    if (id == -1)
    {
        ui->statusbar->showMessage("User is not found!");
        return;
    }
    User user;
    user.SetName("AddedUser");
    user.SetId(id);
    current_room->AddMember(user);
    ui->listMembers->addItem(QString::fromStdString(user.GetName()));
}

void MainWindow::on_pushButton_3_clicked()
{
    CreateRoomForm room_form(this, this);
    room_form.setModal(true);
    room_form.exec();
}
