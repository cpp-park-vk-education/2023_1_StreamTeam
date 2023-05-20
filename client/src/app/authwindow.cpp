#include "authwindow.h"
#include "ui_authwindow.h"
#include "mainwindow.h"
#include "session.hpp"
#include "../../../include/json.hpp"

#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent, MainWindow *main) :
    QDialog(parent),
    mainwind(main),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    setWindowTitle("Log in");
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::on_pushButton_clicked()
{
    QString login = ui->line_login->text();
    QString password = ui->line_password->text();

    nlohmann::json_abi_v3_11_2::json data = {
        {"method", "auth"},
        {"data",
            {
                {"type", "email"},
                {"name", login.toStdString()},
                {"password", password.toStdString()}
            }
        }
    };

// Преобразуем json в строку
    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString);

    // Отправляем запрос на сервер, получаем какой-то ответ
    if (login == "iu3" && password == "123")
    {
        auth_success = true;
        std::shared_ptr<User> user(new User);
        user->SetName(login.toStdString());
        user->SetPassword(password.toStdString());
        user->SetId(3);
        mainwind->Authenticate(user);
        accept();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Log in error", "Incorrect login or password");
    }
}


void AuthWindow::on_AuthWindow_rejected()
{
    mainwind->quitApp();
}


void AuthWindow::on_pushButtonSignIn_clicked()
{
    QString login = ui->line_login->text();
    QString password = ui->line_password->text();

    nlohmann::json_abi_v3_11_2::json data = {
            {"method", "create"},
            {"data",
                       {
                               {"username", "hello"},
                               {"email", login.toStdString()},
                               {"password", password.toStdString()}
                       }
            }
    };

    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString);
//    {"method":"create","data":{"username":"aon","password":"1234","email":"abc@mail.ru"}}
}
