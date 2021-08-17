#ifndef WORD_MODEL_H
#define WORD_MODEL_H

#include <QAbstractItemModel>

class Word_Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit Word_Model(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;




protected:

    static const QString NEWROWMARKER;

    QHash<QString, QString>     _keyFields;
    QHash<QString, QString>     _editFields;
    bool                        _insertRowMode;


};

#endif // WORD_MODEL_H
