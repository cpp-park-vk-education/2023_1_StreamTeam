#include "mainwindow.h"
#include "authwindow.h"

#include <user.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    AuthWindow authWindow(&w, &w);
    authWindow.setModal(true);
    authWindow.exec();

    return a.exec();
}
