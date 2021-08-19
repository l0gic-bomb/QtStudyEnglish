#include "word_model.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

#include <QDebug>

const QString MARKER = "marker";

Word_Model::Word_Model(QObject *parent) : POS_Model(parent)
{
}

void Word_Model::setTablesDesc(QList<TableDescription> &listDesc) noexcept
{
    beginResetModel();

    _keyColumns.clear();
    _editColumns.clear();
    _listDesc.clear();

    _listDesc = listDesc;

    foreach (const TableDescription& desc, _listDesc) {
        foreach (const QString& field, desc.keys)
            _keyColumns.insert(field, desc.name);
        foreach (const QString& field, desc.fields)
            _editColumns.insert(field, desc.name);
    }

    endResetModel();
}

bool Word_Model::submitNewRows()
{

}

bool Word_Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (index.row() >= _data.count())
        return false;
    if (role != Qt::EditRole)
        return false;
    QVariantHash hash = _data.value(index.row());
    QString field = _columnOrder.value(index.column());
    hash.insert(field, value);

    if (!hash.contains(MARKER)) {
        if (!updateValueInDB(hash, field))
            return false;
        _data.replace(index.row(), hash);
        emit dataChanged(index, index, QVector <int>({Qt::EditRole,
                                                      Qt::UserRole
                                                     }));
        return true;
    }
    else
        _data.replace(index.row(), hash);

    emit dataChanged(index, index, QVector <int>({Qt::EditRole,
                                                  Qt::UserRole,
                                                 }));
    return false;
}

Qt::ItemFlags Word_Model::flags(const QModelIndex &index) const
{
    QString column   = _columnOrder.at(index.column());
    Qt::ItemFlags fl = POS_Model::flags(index);

    if (_insertMode)  {
        if (_data.at(index.row()).contains(MARKER))  {
            if (_editColumns.contains(column) || _keyColumns.contains(column))
                fl |= Qt::ItemIsEditable;
            else
                fl = fl & ~Qt::ItemIsEnabled;
        }
        else
            fl = fl & ~Qt::ItemIsEnabled;
    }
    else {
        if (_listDesc.length() != 0) {
            if (_editColumns.contains(column))
                fl |= Qt::ItemIsEditable;
            else
                fl = fl & ~Qt::ItemIsEditable;
        }
        else
            fl = POS_Model::flags(index);
    }


    return  fl;
}

bool Word_Model::insertRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;
    if (count != 1)
        return false;

    beginInsertRows(parent, row, row + count - 1);

    QVariantHash hash;
    hash.insert(MARKER, QVariant());

    for (const TableDescription &desc : _listDesc) {
        QHashIterator<QString, QVariant> it (desc.defaultRow);
        while (it.hasNext()) {
            it.next();
            hash.insert(it.key(), it.value());
        }
    }

    _data.insert(row, hash);
    _insertMode = true;
    endInsertRows();


    return true;
}

bool Word_Model::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;
    if (count != 1)
        return false;

    beginRemoveRows(parent, row, row + count -1);
    QVariantHash hash = _data.at(row);
    if (_insertRowMode) {
        if (hash.contains(MARKER))
        {
            _insertRowMode = false;
            _container.removeAt(row);
        }
        else
        {
            endRemoveRows();
            return false;
        }
    }
    else
    {
        if (!removeRowFromDB(hash))
        {
            endRemoveRows();
            return false;
        }
        _container.removeAt(row);
    }
    endRemoveRows();
    emit dataChanged(index(0,0), index(_container.count() - 1, columnCount() - 1));
    return  true;
}


