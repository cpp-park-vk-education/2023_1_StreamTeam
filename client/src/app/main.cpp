#include "mainwindow.h"
#include "authwindow.h"

#include <user.hpp>
#include <session.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8080");
    Session::setInstance(io_context, endpoints);
    std::thread t([&io_context]() {
        io_context.run();
    });


    MainWindow w;
    w.show();
    AuthWindow authWindow(&w, &w);
    authWindow.setModal(true);
    authWindow.exec();

    return a.exec();
}
