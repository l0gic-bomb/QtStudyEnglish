#ifndef CONNECTIONEDITDIALOG_H
#define CONNECTIONEDITDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionEditDialog;
}

class ConnectionEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionEditDialog(QWidget *parent = nullptr);
    ~ConnectionEditDialog();

private:
    Ui::ConnectionEditDialog *ui;
};

#endif // CONNECTIONEDITDIALOG_H
