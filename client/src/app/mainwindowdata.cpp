#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdynamicbutton.h"


void MainWindow::loadRoomList()
{
    if (user_rooms.size() == 0)
    {
        ui->labelRoomList->show();
        ui->labelRoomList->setText("No Rooms Found");
        return;
    }
    ui->labelRoomList->hide();

    for (size_t i = 0; i < user_rooms.size(); ++i)
    {
        // Создаем объект динамической кнопки
        QDynamicButtonRoom *button = new QDynamicButtonRoom(this);
        button->setText(QString::fromStdString(user_rooms[i]->GetName()));
        button->setObjectPtr(user_rooms[i]);

        ui->verticalLayoutRooms->addWidget(button);
        connect(button, SIGNAL(clicked()), this, SLOT(slotSetCurrentRoom()));
    }
}

void MainWindow::loadCurrentRoom()
{
    clearCurrentRoom();
    ui->listMessages->clear();
    ui->listMembers->clear();
    ui->labelCurrentRoom->setText(QString::fromStdString(current_room->GetName()));
    ui->lineEditmessage->show();
    ui->pushButton_send->show();
    ui->labelMembers->show();
    ui->pushButtonPlayer->show();
    if(login_user->GetId() == current_room->GetLeaderId())
    {
        ui->lineEditAddMember->show();
        ui->pushButton_AddMember->show();
    }

}

void MainWindow::loadMembers()
{
    if (current_room_members.empty())
    {
        ui->listMembers->addItem("No members in this room. How is this possible? You literally see this from inside the room. Consider yourself not-a-human-being, i guess.");
        return;
    }
    for (auto user: current_room_members)
    {
        ui->listMembers->addItem(QString::fromStdString(user->GetName()));
    }
}

void MainWindow::loadMessages()
{
    if (current_room_messages.empty())
    {
        ui->listMessages->addItem("No messages yet");
        return;
    }
    for (auto& mess: current_room_messages)
    {
        addMessage(*mess);
    }
    ui->listMessages->scrollToBottom();
}

void MainWindow::AddRoom(std::shared_ptr<Room> room)
{
    if (user_rooms.empty())
        ui->labelRoomList->hide();
    user_rooms.push_back(room);
    QDynamicButtonRoom *button = new QDynamicButtonRoom(this);
    button->setText(QString::fromStdString(room->GetName()));
    button->setObjectPtr(room);

    ui->verticalLayoutRooms->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(slotSetCurrentRoom()));
}

void MainWindow::addMessage(Message mes)
{
    if (current_room_messages.empty())
        ui->listMessages->clear();
    std::string message = mes.GetAuthorName() + ",  " + mes.GetPostTime() + '\n' + mes.GetTextBody() + '\n';
    ui->listMessages->addItem(QString::fromStdString(message));
}

void MainWindow::clearRoomList()
{
    int size = ui->verticalLayoutRooms->count();
    for(int i = 0; i < size; ++i){
        QDynamicButtonRoom *button = qobject_cast<QDynamicButtonRoom*>(ui->verticalLayoutRooms->itemAt(0)->widget());
            button->hide();
            delete button;
    }
    ui->labelRoomList->setText("Loading...");
    ui->labelRoomList->show();
}

void MainWindow::clearCurrentRoom()
{
    ui->labelCurrentRoom->setText("Choose your Room");
    ui->listMembers->clear();
    ui->listMessages->clear();
    ui->lineEditmessage->hide();
    ui->lineEditmessage->clear();
    ui->pushButton_send->hide();
    ui->labelMembers->hide();
    ui->pushButtonPlayer->hide();
    ui->lineEditAddMember->hide();
    ui->lineEditAddMember->clear();
    ui->pushButton_AddMember->hide();
}
