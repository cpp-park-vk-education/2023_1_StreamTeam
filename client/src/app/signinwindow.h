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
    explicit SignInWindow(QWidget *parent = nullptr, MainWindow *main = nullptr);
    ~SignInWindow();

private slots:
    void showErrorMessage(const QString& title, const QString& message);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SignInWindow *ui;
    MainWindow *mainwind;
};

#endif // SIGNINWINDOW_H
