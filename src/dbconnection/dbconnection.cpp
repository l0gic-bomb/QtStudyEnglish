#include "dbconnection.h"
#include "ui_dbconnection.h"

#include <QFileDialog>

#include <QDebug>


DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent), ui(new Ui::DBConnection)
{
    ui->setupUi(this);

    _state = false;

    connect(ui->btn_selectdb, &QToolButton::clicked,     this, &DBConnection::slSelectFileDB);
    connect(ui->btn_accept,   &QAbstractButton::clicked, this, &DBConnection::slAcceptChanges);
    connect(ui->btn_cancel,   &QAbstractButton::clicked, this, &DBConnection::slCancel);
}

DBConnection::~DBConnection()
{
    delete ui;
}

DBConnection& DBConnection::instance()
{
    static DBConnection instance;
    return instance;
}

void DBConnection::connectDB()
{
    _database = QSqlDatabase::addDatabase("QSQLITE");
    if (_path.isEmpty())
        return;

    _database.setDatabaseName(_path);

    if (!_database.open()) {
        qDebug() << "Не удалось подключиться";
        _state = false;
    } else {
        qDebug() << "Подключение успешно";
        _state = true;
    }
}


bool DBConnection::getState() const
{
    return _state;
}

QSqlDatabase DBConnection::getDatabase() const
{
    return _database;
}

void DBConnection::slSelectFileDB()
{
    if (ui->le_path->text().isEmpty()) {
        QString path = QFileDialog::getOpenFileName(this,
                                                    "Выбор базы данных",
                                                    QString() ,
                                                    "Файл БД SQLite (*.sqlite);;Все файлы(*)",
                                                    nullptr);
        ui->le_path->setText(path);
        _path = path;
    } else
        ui->le_path->setText(_path);
}

void DBConnection::slAcceptChanges()
{
    connectDB();
}

void DBConnection::slCancel()
{
    this->close();
}


