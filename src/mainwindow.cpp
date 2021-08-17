#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _connection = new DBConnection(this);
    _TypeWordModel  = new POS_Model(this);

    ui->pos_view->setModel(_TypeWordModel);


    connect(ui->btn_connection, &QToolButton::clicked, this, &MainWindow::slConnectionDB);
    connect(ui->pos_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::slSelectionItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slConnectionDB()
{
    if (!_connection->exec()) {
        _TypeWordModel->setColumns({{"part_of_speech", "Часть речи"}});
        QString sql = "SELECT * FROM type_word ORDER BY id";
        qDebug() << sql;
        _TypeWordModel->setQuery(sql);
        ui->pos_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }
}

void MainWindow::slSelectionItem()
{
//    QModelIndexList selectionIndexes = ui->pos_view->
}
