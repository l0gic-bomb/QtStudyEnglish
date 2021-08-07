#include "dataconnection.h"

#include <QSqlError>
#include <QApplication>

namespace DBConstConnection {
const QString GROUP_KEY    = "database";
const QString HOST_KEY     = "host";
const QString PORT_KEY     = "port";
const QString DBNAME_KEY   = "dbname";
const QString USERNAME_KEY = "username";
const QString PASSWORD_KEY = "password";
const QString DBTYPE_KEY   = "dbtype";
}

DataConnection* DataConnection::_instance = nullptr;

DataConnection::DataConnection(QObject *parent) : QObject(parent)
{
}

DataConnection::~DataConnection()
{
    delete _params;
}

DataConnection *DataConnection::instance()
{
    if (!_instance)
        _instance = new DataConnection(qApp);

    return _instance;
}

QString DataConnection::host() const
{
    return _params->_host;
}

QString DataConnection::databaseName() const
{
    return _params->_dbName;
}

QString DataConnection::userName() const
{
    return _params->_userName;
}

QString DataConnection::password() const
{
    return _params->_password;
}

QString DataConnection::dbType() const
{
    return _params->_dbType;
}

void DataConnection::setHost(const QString &host)
{
    _params->_host = host;
}

void DataConnection::setDatabaseName(const QString &dbName)
{
    _params->_dbName = dbName;
}

void DataConnection::setUserName(const QString &userName)
{
    _params->_userName = userName;
}

void DataConnection::setPassword(const QString &password)
{
    _params->_password = password;
}

void DataConnection::setDbType(const QString &dbType)
{
    _params->_dbType = dbType;
}

void DataConnection::loadSettings()
{

}

QString DataConnection::errorText()
{

}
