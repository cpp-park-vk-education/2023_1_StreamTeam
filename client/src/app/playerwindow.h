#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QDialog>

namespace Ui {
class PlayerWindow;
}

class PlayerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerWindow(QWidget *parent = nullptr);
    ~PlayerWindow();

private:
    Ui::PlayerWindow *ui;
};

#endif // PLAYERWINDOW_H
