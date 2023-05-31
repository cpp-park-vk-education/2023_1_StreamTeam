#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authwindow.h"
#include "createroomform.h"
#include "qdynamicbutton.h"
#include "playerwindow.h"

#include <QMessageBox>
#include <chrono>

using json = nlohmann::json_abi_v3_11_2::json;

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

    current_room_members.clear();
    current_room_members.shrink_to_fit();
    //

    clearRoomList();
    clearCurrentRoom();

//    if (player)
//        delete player;
//    player = nullptr;

    AuthWindow authWindow(this, this);
    authWindow.setModal(true);
    authWindow.exec();
}

void MainWindow::on_pushButtonPlayer_clicked()
{
    auto session = Session::getInstance();

    json data = {
            {"table", "video"},
            {"method", "startVideo"},
            {"data", "1"}
    };

    std::string jsonString = data.dump();

    std::cout << "Request: " << jsonString << std::endl;
//    json response;

//    std::string x = "rtsp://localhost:8554/stream1";
//    createPlayer(x);


//        auto player = new PlayerWindow(this);


//    player->show();

    session->Send(jsonString, [this](const json& answer) {
        std::cout << "Response got to start stream:" << answer.dump() << std::endl;

        if (answer["status"] == "ok") {
            std::string tmp = "rtsp://localhost:8554/stream";
            //std::string tmp = answer["result"].dump();

            qRegisterMetaType<std::string>("std::string");
            QMetaObject::invokeMethod(this, "createPlayer", Qt::QueuedConnection,
                                      Q_ARG(std::string, tmp));
        } else {
            QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                      Q_ARG(QString, "Player Error"),
                                      Q_ARG(QString, "Could not open player!"));
        }
    });
}

void MainWindow::createPlayer(const std::string& ip_addr) {
    auto player = new PlayerWindow(this, ip_addr);
    player->show();
}

void MainWindow::slotSetCurrentRoom()
{
    QDynamicButtonRoom *button = (QDynamicButtonRoom*) sender();
    auto new_room = button->getObjectPtr();

    {
        json data = {
            {"table", "viewer"},
            {"method", "addUserToRoom"},
            {"data",
                {
                    {"room_id", new_room->getID()},
                }
            }
        };

    // Преобразуем json в строку
        std::string jsonString = data.dump();
        std::cout << "Request: " << jsonString << std::endl;
        auto session = Session::getInstance();

        session->Send(jsonString, [this, new_room](const json& answer) {
            if (answer["status"] == "ok") {
                // Здесь обработчик запроса
                this->current_room_members.clear();
                this->current_room_members.shrink_to_fit();

                this->current_room_messages.clear();
                this->current_room_messages.shrink_to_fit();

                this->current_room = new_room;

                for (auto user_info : answer["result"]) {
                    auto user = std::make_shared<User>();
                    user->SetName(user_info["username"]);
                    user->SetId(user_info["id"]);
                    user->SetEmail(user_info["email"]);
                    this->current_room_members.emplace_back(std::move(user));
                }
                for (auto mess_info : answer["messages"]) {
                    auto mes = std::make_shared<Message>();
                    mes->SetPostTime(mess_info["created_at"]);
                    mes->SetId(mess_info["id"]);
                    mes->SetAuthor(mess_info["authorname"]);
                    mes->SetTextBody(mess_info["message"]);

                    this->current_room_messages.emplace_back(std::move(mes));
                }

                QMetaObject::invokeMethod(this, "loadCurrentRoom", Qt::QueuedConnection);
                QMetaObject::invokeMethod(this, "loadMessages", Qt::QueuedConnection);
                QMetaObject::invokeMethod(this, "loadMembers", Qt::QueuedConnection);

            }
            if (answer["status"] == "error")
                QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                          Q_ARG(QString, "Room Entry Error"),
                                          Q_ARG(QString, "Cannot join the Room, plese try again"));
        });
    }
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

    json data = {
        {"table", "message"},
        {"method", "addMessage"},
        {"data",
            {
                {"message", body}
            }
        }
    };

// Преобразуем json в строку
    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString, [this](const json& answer) {
        if (answer["status"] == "ok") {
            // Здесь обработчик запроса
            auto mes = std::make_shared<Message>();
            mes->SetPostTime(answer["result"][0]["created_at"]);
            mes->SetId(answer["result"][0]["id"]);
            mes->SetAuthor(answer["result"][0]["authorname"]);
            mes->SetTextBody(answer["result"][0]["message"]);

            if (this->current_room_messages.empty())
                ui->listMessages->clear();
            this->current_room_messages.emplace_back(std::move(mes));
            this->ui->lineEditmessage->clear();

            QMetaObject::invokeMethod(this, "addLastMessage", Qt::QueuedConnection);

            ui->listMessages->scrollToBottom();
        }
        if (answer["status"] == "error")
            QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                      Q_ARG(QString, "Send Message Error"),
                                      Q_ARG(QString, "Something went reeeaaally wrong"));
    });

}

//void MainWindow::on_pushButton_AddMember_clicked()
//{
////    if(ui->lineEditAddMember->text() == "")
////        return;
////    int id = ui->lineEditAddMember->text().toInt();
////    for (size_t i = 0; i< current_room->sizeofMembers(); ++i)
////    {
////        if (current_room->GetMember(i).GetId() == id)
////        {
////            ui->statusbar->showMessage("User is already in Room!");
////            return;
////        }
////    }
////    if (id == -1)
////    {
////        ui->statusbar->showMessage("User is not found!");
////        return;
////    }
////    User user;
////    user.SetName("AddedUser");
////    user.SetId(id);
////    current_room->AddMember(user);
////    ui->listMembers->addItem(QString::fromStdString(user.GetName()));
//}

void MainWindow::on_pushButton_3_clicked()
{
    CreateRoomForm room_form(this, this);
    room_form.setModal(true);
    room_form.exec();
}
