#ifndef WORD_MODEL_H
#define WORD_MODEL_H

#include "pos_model.h"
#include <QSet>

struct TableDescription
{
    QString name;
    QSet<QString> keys;
    QSet<QString> fields;
};

class Word_Model : public POS_Model
{
    Q_OBJECT

public:
    explicit Word_Model(QObject *parent = nullptr);
    virtual ~Word_Model() override = default;

    virtual void setTablesDesc(QList<TableDescription>& listDesc) noexcept;
    virtual bool submitNewRows();

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:

    QHash<QString, QString> _keyColumns;
    QHash<QString, QString> _editColumns;
    bool                    _insertMode;
    QList<TableDescription> _listDesc;


};

#endif // WORD_MODEL_H
