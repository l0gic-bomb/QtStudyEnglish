#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _connection = new DBConnection();

    connect(ui->btn_connection, &QToolButton::clicked, this, &MainWindow::slConnectionDB);
    connect(ui->toolButton_4, &QToolButton::clicked, this, &MainWindow::slRemoveAfterThisSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete  _connection;
}

void MainWindow::slConnectionDB()
{
    _connection->exec();
}

void MainWindow::slRemoveAfterThisSlot()
{
    if (_connection->getState()) {
        QSqlQuery _lastQuery(_connection->getDatabase());
        if (!_lastQuery.exec("select * from type_word")) {
            qDebug() << "123";
        }

        while(_lastQuery.next()) {
            qDebug() << _lastQuery.record();
        }

    }
}
