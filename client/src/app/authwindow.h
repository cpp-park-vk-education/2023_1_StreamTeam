#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr, MainWindow *main = nullptr);
    ~AuthWindow();

private slots:
    void on_pushButton_clicked();

    void on_AuthWindow_rejected();

private:
    Ui::AuthWindow *ui;
    MainWindow *mainwind;
    bool auth_success = false;
};

#endif // AUTHWINDOW_H
