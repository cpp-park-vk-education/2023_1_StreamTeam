#ifndef CREATEROOMFORM_H
#define CREATEROOMFORM_H

#include <QDialog>
#include <memory>

#include "room.hpp"
#include "user.hpp"
#include "mainwindow.h"

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
    void on_buttonBox_accepted();

private:
    Ui::CreateRoomForm *ui;
    MainWindow* mainwind;

};

#endif // CREATEROOMFORM_H
