#ifndef WORD_MODEL_H
#define WORD_MODEL_H

#include "pos_model.h"
#include <QSet>

struct TableDescription
{
    QString name;
    QSet<QString> keys;
    QSet<QString> fields;
    QVariantHash  defaultRow;
};

class Word_Model : public POS_Model
{
    Q_OBJECT

public:
    explicit Word_Model(QObject *parent = nullptr);
    virtual ~Word_Model() override = default;

    void setTablesDescriptions(QList<TableDescription>& listDesc) noexcept;
    bool submitNewRows();

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

    QHash<QString, QString> _keyColumns;
    QHash<QString, QString> _editColumns;
    bool                    _insertMode;
    QList<TableDescription> _listDesc;

    bool writeNewRow(QVariantHash& hash);
    bool removeRow(QVariantHash& hash);


};

#endif // WORD_MODEL_H
