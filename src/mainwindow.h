#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>

#include "dbconnection/dbconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slConnectionDB();
    void slRemoveAfterThisSlot();

private:
    Ui::MainWindow *ui;
    DBConnection* _connection;

};
#endif // MAINWINDOW_H
