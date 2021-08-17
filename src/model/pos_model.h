#ifndef POS_MODEL_H
#define POS_MODEL_H

#include <QAbstractItemModel>

class POS_Model : public QAbstractItemModel
{
    Q_OBJECT
public:

    explicit POS_Model(QObject *parent = nullptr);

    virtual ~POS_Model() override = default;

    void setQuery(const QString &query) noexcept;
    void setColumns(const QList<QPair<QString, QString>> &columns) noexcept;
    void setQuery(const QString &query, const QList<QPair<QString, QString>> &columns) noexcept;
    void select() noexcept;
    QVariantHash getRow(int row) const noexcept;
    void setContainer(const QList <QVariantHash> &container, const QList<QPair<QString, QString>> &columns) noexcept;


    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


private:

    QString                     _query;
    QStringList                 _columnOrder;
    QVariantHash                _titles;
    QList <QVariantHash>        _data;

    virtual QVariant processingEditRole(const QModelIndex &index) const noexcept;
    virtual QVariant processingUserRole(const QModelIndex &index) const noexcept;
};
#endif // POS_MODEL_H
