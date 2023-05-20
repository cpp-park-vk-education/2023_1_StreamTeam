#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class SignInWindow;
}

class SignInWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = nullptr, MainWindow *main = nullptr, std::shared_ptr<RequestFormer> request = nullptr);
    ~SignInWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SignInWindow *ui;
    MainWindow *mainwind;
    std::shared_ptr<RequestFormer> Request;
};

#endif // SIGNINWINDOW_H
