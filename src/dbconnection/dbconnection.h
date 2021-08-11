#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class DBConnection;
}

class SettingPath {

};

class DBConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DBConnection(QWidget *parent = nullptr);
    ~DBConnection();

    static DBConnection& instance();

    void connectDB();
    bool getState() const;
    QSqlDatabase getDatabase() const;

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
