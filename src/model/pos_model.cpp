#include "pos_model.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

POS_Model::POS_Model(QObject *parent) : QAbstractItemModel(parent)
{
}

void POS_Model::setQuery(const QString &query) noexcept
{
    _query = query;
    select();
}

void POS_Model::setColumns(const QList<QPair<QString, QString>>& columns) noexcept
{
    _columnOrder.clear();
    _titles.clear();

    for (int i = 0; i < columns.count(); ++i) {
        QPair<QString, QString> pair = columns.at(i);
        _columnOrder.append(pair.first);
        _titles.insert(pair.first, pair.second);
    }
}

void POS_Model::select() noexcept
{
    // Reset our model for new changes
    beginResetModel();

    _data.clear();

    QSqlQuery query;

    if (!query.exec(_query))
            qDebug() << query.lastError().text();

    // work with data
    while (query.next()) {
        QSqlRecord record = query.record();
        QVariantHash hash;
        for (int i = 0; i < record.count(); ++i)
            hash.insert(record.fieldName(i), record.value(i));
        _data.append(hash);
    }

    // Finish reseting our model
    endResetModel();
}

QVariantHash POS_Model::getRow(const int& row) const noexcept
{
    if (row >= _data.count())
        return QVariantHash();

    return _data.at(row);
}

void POS_Model::setContainer(const QList<QVariantHash> &container, const QList<QPair<QString, QString>>& columns) noexcept
{
    beginResetModel();
    setColumns(columns);
    _data = container;
    endResetModel();
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
    if (parent.isValid())
        return 0;

    return _data.count();
}

int POS_Model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _columnOrder.count();
}

QVariant POS_Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();


    switch (role) {
    case Qt::DisplayRole:
        return displayRole(index);
    case Qt::EditRole:
        return displayRole(index);
    case Qt::UserRole:
        return userRole(index);
    default:
        return QVariant();
    }
}

QVariant POS_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Vertical)
        return QVariant();
    if (section >= columnCount())
        return QVariant();
    if (role != Qt::DisplayRole)
        return QVariant();

    QString field = _columnOrder.at(section);
    return _titles.value(field);
}

Qt::ItemFlags POS_Model::flags(const QModelIndex &index) const
{
    // block selectable more rows, only one row can be selectable
    return QAbstractItemModel::flags(index) & ~Qt::ItemIsSelectable;
}

QVariant POS_Model::displayRole(const QModelIndex &index) const noexcept
{
    QString column = _columnOrder.at(index.column());
    return  _data.at(index.row()).value(column);
}

QVariant POS_Model::userRole(const QModelIndex &index) const noexcept
{
    return getRow(index.row());
}
