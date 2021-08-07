#include "dbconnectionmodel.h"

DBConnectionModel::DBConnectionModel(QObject *parent) : QAbstractItemModel(parent)
{
}

QVariant DBConnectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QAbstractItemModel::headerData(section, orientation, role);
}

QModelIndex DBConnectionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return  QModelIndex();
    if (row >= rowCount())
        return  QModelIndex();

    return createIndex(row, column, _listConn.at(row));
}

QModelIndex DBConnectionModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int DBConnectionModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return _listConn.count();
    else
        return 0;
}

int DBConnectionModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 1;
    else
        return 0;
}

QVariant DBConnectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::UserRole)
        return index.row() == _rowCurrent ? true : false;


    return QVariant();
}

bool DBConnectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::UserRole)
    {
        if (value == true)
            _rowCurrent = index.row();
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

void DBConnectionModel::addConnection(DBDesc * const currentConneciton)
{
    beginResetModel();
    _listConn.append(currentConneciton);
    endResetModel();
}

DBDesc *DBConnectionModel::getConnection(const QModelIndex &index) const
{
    if (!index.isValid())
        return Q_NULLPTR;

    return static_cast<DBDesc*>(index.internalPointer());
}
