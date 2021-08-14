#ifndef POS_MODEL_H
#define POS_MODEL_H

#include <QAbstractItemModel>

typedef QList<QPair<QString, QString>> columnList;

class POS_Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public:

    enum ModelRoles {
        DataRole      = Qt::UserRole + 0x1000,
        UpdatedRole   = Qt::UserRole + 0x2101,
        InsertedRole  = Qt::UserRole + 0x2102,
    };
    Q_ENUM(ModelRoles);


    explicit POS_Model(QObject *parent = nullptr);
    ~POS_Model() = default;

    QVariantHash getDataRow(const int& row) const noexcept;

    void setQuery(const QString &query) noexcept;
    void setColumns(const columnList& columns) noexcept;
    void setQuery(const QString &query, const columnList &columns) noexcept;

    void select() noexcept;

    QVariantHash getRow(int row) const noexcept;
    void setDataList(const QList<QVariantHash>& dataList, const columnList& columns) noexcept;


private:
    QString _query;
    QList<QVariantHash> _data;
    QStringList _orderColumn;
    QVariantHash _titelesColumn;

    QList<QVariantHash> _dataList;
};

#endif // POS_MODEL_H
