#include "mainwindow.h"

#include <QApplication>
#include "dbconnection/dbconnection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DBConnection* dbconnection = new DBConnection();
    dbconnection->connectDB();


    MainWindow w;
    w.show();
    delete dbconnection;
    return a.exec();
}
