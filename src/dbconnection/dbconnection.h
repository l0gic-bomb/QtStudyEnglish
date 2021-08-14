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
    bool getState() const noexcept;
    QSqlDatabase getDatabase() const noexcept;

public slots:
    void slSelectFileDB();
    void slAcceptChanges();
    void slCancel();

private:
    Ui::DBConnection  *ui;

    QString _path;
    bool _state;
    QSqlDatabase _database;

};

#endif // DBCONNECTION_H
