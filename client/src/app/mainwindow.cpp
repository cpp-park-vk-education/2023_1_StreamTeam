#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "session.hpp"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SyncView");

    ui->lineEditmessage->hide();
    ui->pushButton_send->hide();
    ui->labelMembers->hide();
    ui->pushButtonPlayer->hide();
    ui->pushButton_films->hide();
    ui->listFilms->hide();
    //player = nullptr;
    current_room = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    QApplication::quit();
}

void MainWindow::Authenticate(std::shared_ptr<User> ptr)
{
    login_user = ptr;
    ui->menuUser_Name->setTitle(QApplication::translate("MainWindow", login_user->GetName().c_str(), nullptr));
    ui->statusbar->showMessage("Login Success!");

    auto session = Session::getInstance();
    nlohmann::json_abi_v3_11_2::json data = {
            {"table", "room"},
            {"method", "getAllRooms"},
            {"data", ""}
    };
    std::string jsonString = data.dump();

    std::cout << "Request: " << jsonString << std::endl;
    nlohmann::json_abi_v3_11_2::json response;

    session->Send(jsonString, [this](const nlohmann::json_abi_v3_11_2::json& answer) {
        if (answer["status"] == "ok") {
            for (auto room_info : answer["result"]) {
                auto room = std::make_shared<Room>();
                room->SetName(room_info["name"]);
                room->setID(room_info["id"]);
                room->SetLeaderId(room_info["creator"]);
                user_rooms.emplace_back(std::move(room));
            }
            ui->listFilms->addItem("cat.mp4");
            ui->listFilms->selectAll();
            QMetaObject::invokeMethod(this, "loadRoomList", Qt::QueuedConnection);
        } else {
            QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                      Q_ARG(QString, "Something went wrong"),
                                      Q_ARG(QString, "Oopsie!"));
        }
    });
}

void MainWindow::showErrorMessage(const QString& title, const QString& message)
{
    QMessageBox::warning(this, title, message);
}

std::shared_ptr<User> MainWindow::getCurrentUser()
{
    return login_user;
}

void MainWindow::quitApp()
{
    close();
}
