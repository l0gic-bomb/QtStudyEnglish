#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QDialog>
#include <QtSql>

/*!
  \brief   Диалог для выбора БД
  \author  Krymov A.O.
  \version 1.0
  \date    14.08.2021

  Диалог предназначен для выбора БД и подключения к ней
*/

namespace Ui {
class DBConnection;
}

class DBConnection : public QDialog
{
    Q_OBJECT
    enum class queryType {
        TABLES,
        DEFAULT
    };

public:
    explicit DBConnection(QWidget *parent = nullptr);
    ~DBConnection();

    //! getter DB
    QSqlDatabase getDatabase() const noexcept;

public slots:
    //! Slot for selecting DB
    void slSelectFileDB();
    //! Slot for accepting changes
    void slAcceptChanges();
    //! Slot for canceling changed
    void slCancel();

private slots:
    //! Slot for creating DB
    void slCreateDB();

private:
    //! creating db
    void doingQuery(const queryType& type);
    //! read query from file
    QStringList readQuery(const QString& path);
    //! open database
    void openDB();
    //! insertind default data
    void insertDefaultWord();

    Ui::DBConnection  *ui;


    QString mName;
    QString mPath;
    QSqlDatabase mDatabase;

};

#endif // DBCONNECTION_H
