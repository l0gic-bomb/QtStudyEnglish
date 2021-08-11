#ifndef CONNECTIONDELEGATE_H
#define CONNECTIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QTextDocument>

class ConnectionDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ConnectionDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
     void fillDocument(QTextDocument* doc, const QModelIndex &index) const; ///< Формирование документа для отображения
};

#endif // CONNECTIONDELEGATE_H
