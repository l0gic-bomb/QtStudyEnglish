#include "connectiondelegate.h"

#include <QPainter>
#include "src/dbconnection/dbconnectionmodel.h"
#include <QTextCharFormat>
#include <QTextCursor>
#include <QtMath>


ConnectionDelegate::ConnectionDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void ConnectionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    painter->save();

    QTextDocument td;
    fillDocument(&td, index);
    painter->translate(option.rect.left(), option.rect.top());
    QRect clip(0, 0, option.rect.width(), option.rect.height());
    td.drawContents(painter, clip);

    painter->restore();
}

QSize ConnectionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    QTextDocument td;
    fillDocument(&td, index);
    QSizeF sz = td.size();
    QSize size (qCeil(sz.width()), qCeil(sz.height()));
    return size;
}

void ConnectionDelegate::fillDocument(QTextDocument *doc, const QModelIndex &index) const
{
    DBDesc* desc = static_cast<DBDesc* >(index.internalPointer());
    if (desc == nullptr)
        return;

    QTextCursor cursor(doc);
    cursor.beginEditBlock();

    QTextCharFormat format;
    QFont font;
    font.setBold(true);
    format.setFont(font);
    cursor.insertText(desc->_title, format);


    if (desc->_flags.testFlag(DBDesc::TypeConnection::DefaultFlag))
    {
        font = QFont();
        font.setItalic(true);
        font.setUnderline(true);
        format.setFont(font);
        cursor.insertText("\n", format);
        format.clearForeground();

    }

    format.clearForeground();
    cursor.insertText("\n", format);

    QString db;
    if (desc->_type == "QSQLITE")
        db = desc->_dbName;

    cursor.insertText(db, format);

    cursor.endEditBlock();
}

