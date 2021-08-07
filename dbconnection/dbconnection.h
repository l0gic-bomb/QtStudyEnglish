#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>

#include "dbconnection/dbconnectionmodel.h"
#include "dbconnection/dataconnection.h"

namespace Ui {
class DBConnection;
}

class DBConnection : public QDialog
{
    Q_OBJECT

public:
    explicit DBConnection(QWidget *parent = nullptr);
    ~DBConnection();

    void loadDefaultConnection();

public slots:
    void slAddConnection();

private:
    Ui::DBConnection  *ui;
    DBConnectionModel *_modelConnection;

};

#endif // DBCONNECTION_H
