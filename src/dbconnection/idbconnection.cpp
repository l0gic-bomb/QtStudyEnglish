#include "idbconnection.h"
#include "ui_idbconnection.h"

#include "dbconnection.h"

static QMetaObject::Connection autoDelSingleton;
IDBConnection* IDBConnection::_self = Q_NULLPTR;

IDBConnection::IDBConnection(QWidget *parent) :
    QDialog(parent)
{
}

IDBConnection::~IDBConnection()
{

}

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
        _self = new DBConnection(QApplication::activeWindow());
        if (!autoDelSingleton)
            autoDelSingleton = connect(qApp, &QCoreApplication::aboutToQuit, deleteInstance);
    }

    return _self;
}

void IDBConnection::deleteInstance()
{
    delete _self;
    _self = Q_NULLPTR;
}
