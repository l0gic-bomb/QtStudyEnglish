#include "dbconnection.h"
#include "ui_dbconnection.h"

#include <QDebug>
#include <QUuid>
#include <QFile>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "src/dbconnection/connectioneditdialog.h"

DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnection)
{
    ui->setupUi(this);

    _modelConnection = new DBConnectionModel(this);

    ui->listView->setModel(_modelConnection);

    connect(ui->btn_add, &QToolButton::clicked, this, &DBConnection::slAddConnection);
}

DBConnection::~DBConnection()
{
    delete ui;
}

DBConnection::ConnectionResult DBConnection::connectDB()
{
    loadDefaultConnection();

    if (_currentConnection == nullptr) {
        qDebug() << "Не указано подключение";
        return DBConnection::Error;
    }

    QString connName      = QUuid::createUuid().toString();
    QSqlDatabase database = QSqlDatabase::addDatabase(_currentConnection->_type, connName);
    database.setHostName(_currentConnection->_host);
    database.setPort(_currentConnection->_port);
    database.setUserName(_currentConnection->_userName);
    database.setPassword(_currentConnection->_password);
    database.setDatabaseName(_currentConnection->_dbName);

//    if (_currentConnection->_type == "QSQLITE") {
//        QFile
//    }
}

void DBConnection::loadDefaultConnection()
{
    DataConnection* dataConnection = DataConnection::instance();

    if (dataConnection->dbType().isEmpty())
        return;
    else if ((dataConnection->dbType() == "QSQLITE" && dataConnection->databaseName().isEmpty()))
        return;

    DBDesc* desc = new DBDesc();

    desc->_host     = dataConnection->host();
//    desc->_port     = dataConnection->port();
    desc->_userName = dataConnection->userName();
    desc->_password = dataConnection->password();
    desc->_dbName   = dataConnection->databaseName();
    desc->_type     = dataConnection->dbType();

    desc->_title = "Соединение из конф. файла";

    _modelConnection->addConnection(desc);
}

void DBConnection::slAddConnection()
{
    ConnectionEditDialog* edit = new ConnectionEditDialog(this);
    QList<DBDesc*> list = edit->getNewConnection();

//    ConnEditDialog* dlg = new ConnEditDialog(this);
//    QList<DBConnDesc*> list = dlg->getNewConnection();
//    foreach(DBConnDesc* desc, list)
//        _model->addConnection(desc);

//    if (_model->rowCount() == 1)
//    {
//        QModelIndex index = _model->index(0, 0);
//        _model->getConnection(index)->_flags.setFlag(DBConnDesc::fDefault);
//        emit _model->dataChanged(index,index);
//    }

//    delete dlg;
}
