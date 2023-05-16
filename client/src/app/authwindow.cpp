#include "authwindow.h"
#include "ui_authwindow.h"
#include "mainwindow.h"

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

