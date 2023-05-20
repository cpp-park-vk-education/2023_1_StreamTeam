#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent, std::shared_ptr<RequestFormer> request):
    QMainWindow(parent),
    Request(request),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SyncView");

    ui->lineEditmessage->hide();
    ui->pushButton_send->hide();
    ui->labelMembers->hide();
    ui->pushButtonPlayer->hide();
    ui->pushButton_AddMember->hide();
    ui->lineEditAddMember->hide();
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

    /* хардкодим заглушки для обьектов
    std::shared_ptr<Room> room1(new Room),
                          room2(new Room),
                          room3(new Room);
    User user; Message mes;

    room1->SetName("Room number 1");
    user.SetName("Ivan"); room1->AddMember(user);
    user.SetName("Petr"); room1->AddMember(user);
    user.SetName("Vova"); room1->AddMember(user);
    mes.SetAuthor(room1->GetMember(0)); mes.SetPostTime("15:34"); mes.SetTextBody("Hello everynyan! How are you?"); room1->AddMessage(mes);
    mes.SetAuthor(room1->GetMember(2)); mes.SetPostTime("15:35"); mes.SetTextBody("oh mah gahd!!!"); room1->AddMessage(mes);
    mes.SetAuthor(room1->GetMember(0)); mes.SetPostTime("15:35"); mes.SetTextBody("Thank you"); room1->AddMessage(mes);
    room1->SetLeaderId(0);
    user_rooms.push_back(room1);

    room2->SetName("Second room");
    user.SetName("Goga"); room2->AddMember(user);
    user.SetName("Boga"); room2->AddMember(user);
    mes.SetAuthor(room2->GetMember(0)); mes.SetPostTime("4:15"); mes.SetTextBody("Good night"); room2->AddMessage(mes);
    room2->SetLeaderId(0);
    user_rooms.push_back(room2);

    room3->SetName("It is third one!");
    user.SetName("Danya"); room3->AddMember(user);
    user.SetName("Vanya"); room3->AddMember(user);
    user.SetName("Vasya"); room3->AddMember(user);
    user.SetName("iu3"); room3->AddMember(user);
    mes.SetAuthor(room3->GetMember(3)); mes.SetPostTime("4:20"); mes.SetTextBody("HELLO!"); room3->AddMessage(mes);
    room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes);
    room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes);
    room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes);
    room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes); room3->AddMessage(mes);
    room3->SetLeaderId(3);
    user_rooms.push_back(room3);
    */

    loadRoomList();
}

std::shared_ptr<User> MainWindow::getCurrentUser()
{
    return login_user;
}

void MainWindow::quitApp()
{
    close();
}

