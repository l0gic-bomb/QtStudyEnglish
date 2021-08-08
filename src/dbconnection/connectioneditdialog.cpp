#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"

#include <QDebug>

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionEditDialog)
{
    ui->setupUi(this);

    connect(ui->btn_cancel, &QAbstractButton::clicked, this, &ConnectionEditDialog::slReject);
    connect(ui->btn_ok,     &QAbstractButton::clicked, this, &ConnectionEditDialog::slAccept);
}

ConnectionEditDialog::~ConnectionEditDialog()
{
    delete ui;
}

QList<DBDesc *> ConnectionEditDialog::getNewConnection()
{
    if (exec() != Accepted)
        return QList<DBDesc*>();

    QString typeDB = ui->cb_type->currentData().toString();
    if (typeDB == "SQLITE") {
        DBDesc* desc = new DBDesc();

        desc->_type     = typeDB;
        desc->_dbName   = ui->le_filedb->text();
        desc->_port     = ui->sb_port->value();
        desc->_userName = ui->le_login->text();
        desc->_password = ui->le_password->text();
        desc->_title    = ui->le_nameconn->text();

        QList<DBDesc*> listDesc;
        listDesc.append(desc);
        return listDesc;
    } else
        return QList<DBDesc*>();
}

void ConnectionEditDialog::slReject()
{
    this->close();
}

void ConnectionEditDialog::slAccept()
{
    if (ui->le_filedb->text().isEmpty()) {
        qDebug() << "Не указано имя подключения";
        return;
    }

    QString currentTypeDB = ui->cb_type->currentData().toString();
    if (currentTypeDB == "QSQLITE") {
        if (!checkResultConn())
            return;
    } else
        return;

    return QDialog::accept();
}

bool ConnectionEditDialog::checkResultConn()
{
    if (ui->le_filedb->text().isEmpty()) {
        qDebug() << "Не указан путь к файлу или директории";
        return false;
    } else
        return true;

}
