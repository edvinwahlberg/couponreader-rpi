#include "mainwindow.h"
#include <QApplication>

#include <boost/system/error_code.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
