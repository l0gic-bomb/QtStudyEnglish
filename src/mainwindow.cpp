#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    _connection = new DBConnection();
    _leftModel  = new POS_Model(this);

//    _connection->connectDB();
    test();

    ui->left_view->setModel(_leftModel);





    connect(ui->btn_connection, &QToolButton::clicked, this, &MainWindow::slConnectionDB);
    connect(ui->btn_addword, &QToolButton::clicked, this, &MainWindow::slRemoveAfterThisSlot);

}

// C:/Users/Alexey/Documents/QtStudyEnglish/db/qtstudyenglish.sqlite

MainWindow::~MainWindow()
{
    delete ui;
//    delete  _connection;
}

void MainWindow::test()
{
    _leftModel->setColumns({{"part_of_speech", "Часть речи"}});
    QString sql = "SELECT * FROM type_word ORDER BY id";
    qDebug() << sql;
    _leftModel->setQuery(sql);
}

void MainWindow::slConnectionDB()
{
//    _connection->exec();
}



void MainWindow::slRemoveAfterThisSlot()
{

}
