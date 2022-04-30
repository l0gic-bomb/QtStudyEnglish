#include "word_model.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

#include <QDebug>

const QString MARKER = "marker";

Word_Model::Word_Model(QObject *parent) : POS_Model(parent), _insertMode(false)
{
}

void Word_Model::setTablesDescriptions(QList<TableDescription> &listDesc) noexcept
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
    QSqlDatabase db = QSqlDatabase::database();
    // start the transaction with db
    db.transaction();

    for (int i = 0; i < _data.size(); ++i) {
        QVariantHash hash {_data.at(i)};
        if (hash.contains(MARKER)) {
            if (!writeNewRow(hash)) {
                db.rollback();
                return false;
            }
            _data[i] = hash;
        }
    }

    // submit changes
    db.commit();

    _insertMode = true;
    // send signal for changing data in model
    for (int i = 0; i < _data.size(); ++i) {
        QVariantHash hash {_data.at(i)};
        emit dataChanged(index(i,0),
                         index(i, columnCount() - 1),
                         QVector<int>({Qt::DisplayRole,
                                       Qt::EditRole}));
    }

    return true;
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

    if (!hash.contains(MARKER)) // Если строка уже есть в БД
    {
        if (!updateRow(hash, field))
            return false;
        _data.replace(index.row(), hash);
        emit dataChanged(index, index, QVector <int>({Qt::EditRole,
                                                     }));
        return true;
    }
    else
        _data.replace(index.row(), hash);

    emit dataChanged(index, index, QVector <int>({Qt::EditRole,
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

        } else
            fl = fl & ~Qt::ItemIsEnabled;
    } else {
        if (_listDesc.length() != 0) {

            if (_editColumns.contains(column))
                fl |= Qt::ItemIsEditable;
            else
                fl = fl & ~Qt::ItemIsEditable;

        } else
            fl = POS_Model::flags(index);
    }


    return fl;
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

    beginRemoveRows(parent, row, row + count - 1);
    QVariantHash hash = _data.at(row);
    if (_insertMode) {
        if (hash.contains(MARKER)) {
            _insertMode = false;
            _data.removeAt(row);
        } else {
            endRemoveRows();
            return false;
        }
    } else {
        if (!removeRow(hash)) {
            endRemoveRows();
            return false;
        }
        _data.removeAt(row);
    }

    endRemoveRows();
    emit dataChanged(index(0,0), index(_data.count() - 1, columnCount() - 1));
    return  true;
}

QVariant Word_Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    // add role
    default:
        return POS_Model::data(index, role);
    }
}

bool Word_Model::writeNewRow(QVariantHash &hash)
{
    QString sqlInsert  = "INSERT INTO %tablename% (%columns%) VALUES (%values%)";
    for (int i = 0; i < _listDesc.size(); ++i) {
        TableDescription currentDesc = _listDesc.at(i);

        const QStringList columnsList; // = currentDesc.fields.unite(currentDesc.keys).toList();`
        const QString allColumnsString = columnsList.join(",");

        QString values;
        for (int j = 0; j < columnsList.size(); ++j) {
            if (j == columnsList.size() - 1) {
                values.append(":" + columnsList.at(j));
                continue;
            }
            values.append(":" + columnsList.at(j) + ",");
        }


        sqlInsert.replace("%tablename%", currentDesc.name);
        sqlInsert.replace("%columns%",   allColumnsString);
        sqlInsert.replace("%values%",    values);

        QSqlQuery query;
        query.prepare(sqlInsert);
        for (const QString& column: columnsList)
            query.bindValue((":") + column, hash.value(column));

        if (!query.exec()) {
            // add error
            return false;
        }


        const QString &lastId = query.lastInsertId().toString();
        sqlInsert = QString("SELECT %1 FROM %2 WHERE rowid = :rowid").arg(allColumnsString).arg(currentDesc.name);
        if (sqlInsert.isEmpty()) {
            // add error
            return false;
        }

        query.prepare(sqlInsert);
        query.bindValue(":rowid", lastId);

        query.next();
        QSqlRecord record = query.record();
        for (int i = 0; i < record.count(); ++i)
            hash.insert(record.fieldName(i), record.value(i));

    }
    return true;
}

bool Word_Model::removeRow(QVariantHash &hash)
{
    if (_listDesc.size() == 0)
        return false;

    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    for (int i = 0; i < _listDesc.size(); ++i) {
        TableDescription desc = _listDesc.at(i);

        if (desc.name.isEmpty())
            continue;
        if (desc.keys.isEmpty())
            continue;

        QString strQuery = QString("DELETE FROM %table% WHERE %where%");
        strQuery.replace("%table%", desc.name);

        QStringList strList;
        for (const QString& key: desc.keys)
            strList.append(key + "=:" + key);

        strQuery.replace("%where%", strList.join(" AND "));

        QSqlQuery query;
        query.prepare(strQuery);
        for (const QString& key : desc.keys)
            query.bindValue(":" + key, hash.value(key));

        if (!query.exec()) {
            // add error
            db.rollback();
            return false;
        }
    }

    db.commit();
    return true;
}

bool Word_Model::updateRow(const QVariantHash &hash, const QString &field)
{
    if (_listDesc.count() == 0)
        return false;

    QString destTable;
    QStringList keys;
    for (int i = 0; i < _listDesc.count(); ++i)
    {
        TableDescription desc = _listDesc.at(i);
        if (desc.fields.contains(field))
        {
            destTable = desc.name;
           // keys = QStringList(desc.keys.toList());
            break;
        }
    }
    if (destTable.isEmpty())
        return false;
    if (keys.isEmpty())
        return false;


    QString strQuery = QString("UPDATE %table% SET %field% = :%field% WHERE %where%")
            .replace("%table%", destTable).replace("%field%",field);

    QStringList pairs;
    for (const QString &str : keys)
        pairs.append(str + "=:" + str);
    strQuery.replace("%where%", pairs.join(" AND "));

    QSqlQuery query;
    query.prepare(strQuery);
    for (const QString &str : keys)
        query.bindValue(":" + str, hash.value(str));

    query.bindValue(":" + field, hash.value(field));

    if (!query.exec())
        return false;


    return true;
}


