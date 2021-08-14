#include "pos_model.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

POS_Model::POS_Model(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant POS_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();
    if (section >= columnCount())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    QString field = _orderColumn.at(section);
    return _titelesColumn.value(field);
}

QModelIndex POS_Model::index(int row, int column, const QModelIndex &parent) const
{
    if (row > rowCount() || column > columnCount())
        return QModelIndex();

    if (parent.isValid())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex POS_Model::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int POS_Model::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return _data.count();
}

int POS_Model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    Q_UNUSED(parent)
    return _orderColumn.count();
}

QVariant POS_Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
    {
        QString field = _orderColumn.at(index.column());
        return  _data.at(index.row()).value(field);
    }
    case ModelRoles::DataRole:
    {
        QVariant value = getDataRow(index.row());
        return value;
    }
    default:
        return QVariant();
    }
}

Qt::ItemFlags POS_Model::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags &= ~Qt::ItemIsEditable;
    return QAbstractItemModel::flags(index) & ~Qt::ItemIsEditable;
}

QVariantHash POS_Model::getDataRow(const int &row) const noexcept
{
    if (row >= _data.count())
        return QVariantHash();

    return _data.at(row);
}

void POS_Model::setQuery(const QString &query) noexcept
{
    _query = query;
    select();
}

void POS_Model::setColumns(const columnList &columns) noexcept
{
    _orderColumn.clear();
    _titelesColumn.clear();

    for (auto column : columns) {
        QPair<QString, QString> tmpPair = column;
        _orderColumn.append(tmpPair.first);
        _titelesColumn.insert(tmpPair.first, tmpPair.second);
    }
}

void POS_Model::setQuery(const QString &query, const columnList &columns) noexcept
{
    setColumns(columns);
    setQuery(query);
}

void POS_Model::select() noexcept
{
    beginResetModel();

    _dataList.clear();

    QSqlQuery query;

    if (!query.exec(_query))
        qDebug() << query.lastError().text();

    while (query.next()) {
        QSqlRecord record = query.record();
        QVariantHash hash;
        for (int i = 0; i < record.count(); ++i)
            hash.insert(record.fieldName(i), record.value(i));
        _dataList.append(hash);
    }

    QList<QVariantHash> rows = _dataList;
    endResetModel();
}

void POS_Model::setDataList(const QList<QVariantHash> &dataList, const columnList &columns) noexcept
{
    beginResetModel();
    setColumns(columns);
    _dataList = dataList;
    endResetModel();
}
