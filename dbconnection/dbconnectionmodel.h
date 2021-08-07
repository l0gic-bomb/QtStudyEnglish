#ifndef DBCONNECTIONMODEL_H
#define DBCONNECTIONMODEL_H

#include <QAbstractItemModel>

struct DBConnectionDescription {
    enum class TypeConnection {
        DefaultFlag,
        NoFlag
    };

    QString           _type;
    QString           _host;
    int               _port;
    QString           _dbName;
    QString           _userName;
    QString           _password;
    QString           _title;

    TypeConnection    _flags;

};

typedef DBConnectionDescription DBDesc;

class DBConnectionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DBConnectionModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void addConnection(DBDesc* const currentConneciton);
    DBDesc* getConnection(const QModelIndex &index) const;

private:
    QList<DBDesc*> _listConn;
    int _rowCurrent;
};

#endif // DBCONNECTIONMODEL_H
