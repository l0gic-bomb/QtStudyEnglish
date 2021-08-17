#include "word_model.h"

Word_Model::Word_Model(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant Word_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex Word_Model::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex Word_Model::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int Word_Model::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int Word_Model::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant Word_Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
