#include "signinwindow.h"
#include "ui_signinwindow.h"
#include "user.hpp"
#include "requestformer.hpp"

#include <QMessageBox>

SignInWindow::SignInWindow(QWidget *parent, MainWindow *main, std::shared_ptr<RequestFormer> request) :
    QDialog(parent),
    mainwind(main),
    Request(request),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);
    setWindowTitle("Sign in");
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::on_buttonBox_accepted()
{
    std::string name = ui->lineEditName->text().toStdString();
    std::string email = ui->lineEditEmail->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();
    User new_user;
    new_user.SetName(name);
    new_user.SetPassword(password);

    //send to server;
    std::shared_ptr<User> user = Request->NewUser(new_user);
    if (user)
    {
        QMessageBox::information(this, "Sign in success", "Account has been created!");
        mainwind->Authenticate(user);
        accept();
        close();
    }
    else
    {
        QMessageBox::critical(this, "Sign in error", "Coud not create Account");
        return;
    }
}


void SignInWindow::on_buttonBox_rejected()
{
    reject();
}

