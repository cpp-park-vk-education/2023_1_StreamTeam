#ifndef CREATEROOMFORM_H
#define CREATEROOMFORM_H

#include <QDialog>
#include <memory>

#include "room.hpp"
#include "user.hpp"
#include "mainwindow.h"


Q_DECLARE_METATYPE(Room)
Q_DECLARE_METATYPE(std::shared_ptr<Room>)

namespace Ui {
class CreateRoomForm;
}

class CreateRoomForm : public QDialog
{
    Q_OBJECT


public:
    explicit CreateRoomForm(QWidget *parent = nullptr, MainWindow *main = nullptr);
    ~CreateRoomForm();

private slots:
    void showErrorMessage(const QString& title, const QString& message);

    void MainAddRoom(std::shared_ptr<Room>);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateRoomForm *ui;
    MainWindow* mainwind;

};

#endif // CREATEROOMFORM_H
