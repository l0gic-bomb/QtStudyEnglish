#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DBConnection;
}

class DBConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DBConnection(QWidget *parent = nullptr);
    ~DBConnection();

    void connectDB();
    QSqlDatabase getDatabase() const noexcept;

public slots:
    void slSelectFileDB();
    void slAcceptChanges();
    void slCancel();

private:
    Ui::DBConnection  *ui;

    QString _path;
    QSqlDatabase _database;

};

#endif // DBCONNECTION_H
