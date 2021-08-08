#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>

#include "src/dbconnection/dbconnectionmodel.h"
#include "src/dbconnection/dataconnection.h"

namespace Ui {
class DBConnection;
}

class DBConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DBConnection(QWidget *parent = nullptr);
    ~DBConnection();

    enum ConnectionResult
    {
        Okay = 0,                   ///< Успешное подключение
        Error = 1,                ///< Ошибка подключения
        SQLitePathNotExists = 2   ///< Не удается создать файл БД, так как путь не существует
    };
    Q_ENUM(ConnectionResult);

    ConnectionResult connectDB();

    void loadDefaultConnection();


public slots:
    void slAddConnection();

private:
    Ui::DBConnection  *ui;
    DBConnectionModel *_modelConnection;
    DBDesc* _currentConnection;

};

#endif // DBCONNECTION_H
