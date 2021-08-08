#ifndef CONNECTIONEDITDIALOG_H
#define CONNECTIONEDITDIALOG_H

#include <QDialog>

#include "dbconnectionmodel.h"

namespace Ui {
class ConnectionEditDialog;
}

class ConnectionEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionEditDialog(QWidget *parent = nullptr);
    ~ConnectionEditDialog();

    QList<DBDesc*> getNewConnection();

public slots:
    void slReject();
    void slAccept();

private:
    bool checkResultConn();

private:
    Ui::ConnectionEditDialog *ui;
};

#endif // CONNECTIONEDITDIALOG_H
