#include "dbconnection.h"
#include "ui_dbconnection.h"

#include <QDebug>
#include <QUuid>
#include <QFile>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QFileInfo>
#include <QDir>

#include "src/dbconnection/connectioneditdialog.h"
#include "src/dbconnection/connectiondelegate.h"

DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnection)
{
    ui->setupUi(this);

    ui->listView->setItemDelegate(new ConnectionDelegate(this));

    _modelConnection = new DBConnectionModel(this);
    ui->listView->setModel(_modelConnection);

    DBDesc* desc = new DBDesc();
    desc->_host = int(100);
    desc->_userName = "";
    desc->_password = "";
    desc->_dbName   = "C:\\Users\\Alexey\\Documents\\QtStudyEnglish\\db\\qtstudyenglish.sqlite";
    desc->_type     = "QSQLITE";
    desc->_title    = "Соединение по умолчанию";
    _modelConnection->addConnection(desc);

    loadDefaultConnection();

    connect(ui->btn_add, &QToolButton::clicked, this, &DBConnection::slAddConnection);
}

DBConnection::~DBConnection()
{
    delete ui;
    delete _modelConnection;
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

    if (_currentConnection->_type == "QSQLITE")
    {
        QFile file(_currentConnection->_dbName);
        if (!file.exists()) {
            QFileInfo fileInfo(_currentConnection->_dbName);

        }

    }




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
    desc->_port     = 5432;
    desc->_userName = dataConnection->userName();
    desc->_password = dataConnection->password();
    desc->_dbName   = dataConnection->databaseName();
    desc->_type     = dataConnection->dbType();
    desc->_flags    = DBDesc::TypeConnection::NoFlag;
    desc->_title = "Соединение не по умолчанию";

    _modelConnection->addConnection(desc);
}

void DBConnection::slAddConnection()
{
    ConnectionEditDialog* edit = new ConnectionEditDialog(this);
    QList<DBDesc*> list = edit->getNewConnection();
    foreach(DBDesc* desc, list)
        _modelConnection->addConnection(desc);

    if (_modelConnection->rowCount() == 1) {
        QModelIndex index = _modelConnection->index(0, 0);
        _modelConnection->getConnection(index)->_flags.setFlag(DBDesc::TypeConnection::DefaultFlag);
        emit _modelConnection->dataChanged(index,index);
    }

    delete edit;
}

void DBConnection::slDeleteConnection()
{

}

