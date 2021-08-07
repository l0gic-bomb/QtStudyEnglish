#include "dbconnection.h"
#include "ui_dbconnection.h"



DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnection)
{
    ui->setupUi(this);

    _modelConnection = new DBConnectionModel(this);

    ui->listView->setModel(_modelConnection);
}

DBConnection::~DBConnection()
{
    delete ui;
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

}
