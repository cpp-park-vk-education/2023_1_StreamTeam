#include "createroomform.h"
#include "ui_createroomform.h"

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
        return;
    std::string name = ui->lineEditRoomName->text().toStdString();
    std::shared_ptr<Room> room(new Room);
    room->SetName(name);
    room->AddMember(*mainwind->getCurrentUser());
    room->SetLeaderId(mainwind->getCurrentUser()->GetId());
    mainwind->AddRoom(room);
}

