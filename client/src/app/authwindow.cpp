#include "authwindow.h"
#include "ui_authwindow.h"
#include "mainwindow.h"
#include "signinwindow.h"
#include "requestformer.hpp"

#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent, MainWindow *main, std::shared_ptr<RequestFormer> request) :
    QDialog(parent),
    mainwind(main),
    Request(request),
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
    User auth_user;
    auth_user.SetEmail(ui->line_login->text().toStdString());
    auth_user.SetPassword(ui->line_password->text().toStdString());

    std::shared_ptr<User> user = Request->Authenticate(auth_user);
    if (user)
    {
        mainwind->Authenticate(user);
        accept();
        close();
    }
    else
    {
        QMessageBox::warning(this, "Log in error", "Incorrect users credentials");
    }
}


void AuthWindow::on_AuthWindow_rejected()
{
    mainwind->quitApp();
}


void AuthWindow::on_pushButtonSignIn_clicked()
{
    SignInWindow signin(this, mainwind, Request);
    signin.setModal(true);
    bool f = signin.exec();
    if (f)
        accept();
}

