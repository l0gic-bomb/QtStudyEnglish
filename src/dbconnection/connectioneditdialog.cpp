#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"

#include <QDebug>
#include <QFileDialog>

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionEditDialog)
{
    ui->setupUi(this);

    ui->sb_port->setValue(5432);

    connect(ui->btn_cancel,   &QAbstractButton::clicked, this, &ConnectionEditDialog::slReject);
    connect(ui->btn_ok,       &QAbstractButton::clicked, this, &ConnectionEditDialog::slAccept);
    connect(ui->btn_connect,  &QAbstractButton::clicked, this, &ConnectionEditDialog::slSelectionSlot);
}

ConnectionEditDialog::~ConnectionEditDialog()
{
    delete ui;
}

QList<DBDesc *> ConnectionEditDialog::getNewConnection()
{
    if (exec() != Accepted)
        return QList<DBDesc*>();

    QString typeDB = ui->cb_type->currentText();
    if (typeDB == "QSQLITE") {
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
    if (ui->le_nameconn->text().isEmpty()) {
        qDebug() << "Не указано имя подключения";
        return;
    }

    QString currentTypeDB = ui->cb_type->currentText();
    if (currentTypeDB == "QSQLITE") {
        if (!checkResultConn())
            return;
    } else
        return;

    return QDialog::accept();
}

void ConnectionEditDialog::slSelectionSlot()
{
    QString file = QFileDialog::getSaveFileName(this, "Выбор базы данных", QString(), "Файл БД SQLite (*.sqlite);;Все файлы(*)", Q_NULLPTR);
    ui->le_filedb->setText(file);
}


bool ConnectionEditDialog::checkResultConn()
{
    if (ui->le_filedb->text().isEmpty()) {
        qDebug() << "Не указан путь к файлу или директории";
        return false;
    } else
        return true;

}
