#include "mainwindow.h"

#include <QApplication>
#include "dbconnection/dbconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DataConnection::instance()->setDbType("QSQLITE");


    MainWindow w;
    w.show();
    return a.exec();
}
