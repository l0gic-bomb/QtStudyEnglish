#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>

#include "dbconnection/dbconnection.h"
#include "model/pos_model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void test();

public slots:
    void slConnectionDB();
    void slSelectionItem();

signals:
    void sgLoad();

private:
    Ui::MainWindow *ui;
    DBConnection* _connection;
    POS_Model*    _typeWordModel;

    QList<long long> selectedIds();
    QVariantHash getRecord(const QModelIndex& index);



};
#endif // MAINWINDOW_H
