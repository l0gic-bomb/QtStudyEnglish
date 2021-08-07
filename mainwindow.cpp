#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbconnection/dbconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_connection, &QToolButton::clicked, [=](){
        DBConnection dbConnection(this);
        dbConnection.exec();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
