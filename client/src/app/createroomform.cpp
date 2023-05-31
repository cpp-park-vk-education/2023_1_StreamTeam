#include "createroomform.h"
#include "ui_createroomform.h"
#include "mainwindow.h"
#include "room.hpp"
#include "session.hpp"

#include <QMessageBox>
#include <memory>

using json = nlohmann::json_abi_v3_11_2::json;

CreateRoomForm::CreateRoomForm(QWidget *parent, MainWindow* main) :
    QDialog(parent),
    mainwind(main),
    ui(new Ui::CreateRoomForm)
{
    ui->setupUi(this);
    setWindowTitle("Create a new Room");
}

CreateRoomForm::~CreateRoomForm()
{
    delete ui;
}

void CreateRoomForm::on_buttonBox_accepted()
{
    if (ui->lineEditRoomName->text() == "")
        close();
    std::string name = ui->lineEditRoomName->text().toStdString();
    std::shared_ptr<User> leader = mainwind->getCurrentUser();

    json data = {
        {"table", "room"},
        {"method", "addRoom"},
        {"data",
            {
                {"name", name},
                {"creator", leader->GetId()},
                {"current_film", 1},
            }
        }
    };
    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString, [this, name, leader](const json& answer) {
        if (answer["status"] == "ok") {
            // Здесь обработчик запроса

            std::shared_ptr<Room> room(new Room);
            room->SetName(name);
            room->AddMember(*leader);
            room->SetLeaderId(leader->GetId());
            room->setID(answer["result"][0]["id"]);
            //mainwind->AddRoom(room);

            qRegisterMetaType<std::shared_ptr<Room>>("std::shared_ptr<Room>");
            QMetaObject::invokeMethod(this, "MainAddRoom", Qt::QueuedConnection,
                                      Q_ARG(std::shared_ptr<Room>, room));

            close();

        }
        if (answer["status"] == "error")
            QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                      Q_ARG(QString, "Create Room Error"),
                                      Q_ARG(QString, "Something went wrong"));
    });

}

void CreateRoomForm::showErrorMessage(const QString& title, const QString& message)
{
    QMessageBox::warning(this, title, message);
}

void CreateRoomForm::MainAddRoom(std::shared_ptr<Room> room)
{
    mainwind->AddRoom(room);
}

void CreateRoomForm::on_buttonBox_rejected()
{
    close();
}

