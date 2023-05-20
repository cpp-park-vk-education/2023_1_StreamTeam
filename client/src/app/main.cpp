#include "mainwindow.h"
#include "authwindow.h"

#include <requestformer.hpp>
#include <memory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<RequestFormer> Request (new RequestFormer);

    MainWindow w(nullptr, Request);
    w.show();
    AuthWindow authWindow(&w, &w, Request);
    authWindow.setModal(true);
    authWindow.exec();

    return a.exec();
}
