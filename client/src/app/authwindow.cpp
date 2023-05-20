#include "authwindow.h"
#include "ui_authwindow.h"
#include "mainwindow.h"
#include "signinwindow.h"
#include "session.hpp"

#include <QMessageBox>

using json = nlohmann::json_abi_v3_11_2::json;

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
    QString email = ui->line_login->text();
    QString password = ui->line_password->text();

    json data = {
        {"method", "auth"},
        {"data",
            {
                {"type", "email"},
                {"name", email.toStdString()},
                {"password", password.toStdString()}
            }
        }
    };

// Преобразуем json в строку  
    std::string jsonString = data.dump();
    std::cout << "Request: " << jsonString << std::endl;
    auto session = Session::getInstance();
    session->Send(jsonString, [this, email, password](const json& answer) {
        if (answer["status"] == "ok") {
            // Здесь обработчик запроса

            std::shared_ptr<User> user(new User);
            user->SetName(email.toStdString());
            user->SetPassword(password.toStdString());
            user->SetId(answer["result"][0]["id"]);
            user->SetName(answer["result"][0]["username"]);

            QMetaObject::invokeMethod(mainwind, "Authenticate", Qt::QueuedConnection, Q_ARG(std::shared_ptr<User>, user));
            accept();
            close();

        }
        else
            QMetaObject::invokeMethod(this, "showErrorMessage", Qt::QueuedConnection,
                                      Q_ARG(QString, "Login Error"),
                                      Q_ARG(QString, "Something went wrong"));
    });
}

void AuthWindow::showErrorMessage(const QString& title, const QString& message)
{
    QMessageBox::warning(this, title, message);
}

void AuthWindow::on_AuthWindow_rejected()
{
    mainwind->quitApp();
}


void AuthWindow::on_pushButtonSignIn_clicked()
{
    SignInWindow signin(this, mainwind);
    signin.setModal(true);
    bool f = signin.exec();
    if (f)
        accept();
}

