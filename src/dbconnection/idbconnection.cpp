#include "idbconnection.h"
#include "ui_idbconnection.h"



IDBConnection::IDBConnection(QWidget *parent) :
    QDialog(parent)
{
}

IDBConnection::~IDBConnection()
{
}


static QMetaObject::Connection connAutoDelSingleton; // Соединение для удаления синглтона при закрытии программы


IDBConnection* IDBConnection::_self = Q_NULLPTR;


int IDBConnection::exec()
{
    return QDialog::exec();
}

int IDBConnection::exec(QWidget *parent)
{
    setParent(parent);
    setWindowFlags(Qt::Dialog);
    return exec();
}

IDBConnection *IDBConnection::instance()
{
    if (!_self)
    {
//        _self = new DBCon(QApplication::activeWindow());ss
        if (!connAutoDelSingleton)
            connAutoDelSingleton = connect(qApp, &QCoreApplication::aboutToQuit, deleteInstance);
    }

    return _self;
}

void IDBConnection::deleteInstance()
{
    delete _self;
    _self = Q_NULLPTR;
}

IDBConnection::IDBManager(QWidget *parent) : QDialog (parent)
{

}
