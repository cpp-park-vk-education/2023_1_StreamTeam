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

    void on_pushButtonSignIn_clicked();

private:
    Ui::AuthWindow *ui;
    MainWindow *mainwind;
};

#endif // AUTHWINDOW_H
