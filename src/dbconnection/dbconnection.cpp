#include "dbconnection.h"
#include "ui_dbconnection.h"

#include <QFileDialog>

#include <QDebug>


DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent), ui(new Ui::DBConnection)
{
    ui->setupUi(this);

    connect(ui->btn_selectdb, &QToolButton::clicked,     this, &DBConnection::slSelectFileDB);
    connect(ui->btn_accept,   &QAbstractButton::clicked, this, &DBConnection::slAcceptChanges);
    connect(ui->btn_cancel,   &QAbstractButton::clicked, this, &DBConnection::slCancel);
}

DBConnection::~DBConnection()
{
    delete ui;
}

void DBConnection::connectDB()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    _database.setDatabaseName(_path);

    if (!_database.open())
        qDebug() << "Не удалось подключиться";
    else
        qDebug() << "Подключение успешно";
}

QSqlDatabase DBConnection::getDatabase() const noexcept
{
    return _database;
}

void DBConnection::slSelectFileDB()
{
    _path = "E:\\QtStudyEnglish\\db\\qtstudyenglish.sqlite";
    if (_path.isEmpty()) {
        QString path = QFileDialog::getOpenFileName(this,
                                                    "Выбор базы данных",
                                                    QString() ,
                                                    "Файл БД SQLite (*.sqlite)",
                                                    nullptr);
        ui->le_path->setText(path);
        _path = path;
    } else
        ui->le_path->setText(_path);
}

void DBConnection::slAcceptChanges()
{
    connectDB();
    this->close();
}

void DBConnection::slCancel()
{
    this->close();
}


