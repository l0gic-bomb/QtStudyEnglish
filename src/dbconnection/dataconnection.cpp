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
    _params = new ConnectionParams;
    _params->_defaultPort = 5432;
    _params->_defaultHost = "localhost";
    _params->_defaultDbType = "QSQLITE";
    _params->_defaultDbName = "123";

    _params->_port   = _params->_defaultPort;
    _params->_host   = _params->_defaultHost;
    _params->_dbType = _params->_defaultDbType;
    _params->_dbName = _params->_defaultDbName;

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
    return QString();
}
