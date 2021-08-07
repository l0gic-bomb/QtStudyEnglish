#include "connectioneditdialog.h"
#include "ui_connectioneditdialog.h"

ConnectionEditDialog::ConnectionEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionEditDialog)
{
    ui->setupUi(this);
}

ConnectionEditDialog::~ConnectionEditDialog()
{
    delete ui;
}
