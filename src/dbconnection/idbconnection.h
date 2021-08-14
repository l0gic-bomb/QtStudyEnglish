#ifndef IDBCONNECTION_H
#define IDBCONNECTION_H

#include <QDialog>

namespace Ui {
class IDBConnection;
}

class IDBConnection : public QDialog
{
    Q_OBJECT
public:

    /*!
     * \brief Результат подключения к БД
     */
    enum ConnectionResult
    {
        crOK = 0,                   ///< Успешное подключение
        crError = 1,                ///< Ошибка подключения
        crSQLitePathNotExists = 2   ///< Не удается создать файл БД, так как путь не существует
    };


    /*!
     * \brief Подключение к выбранной ранее БД
     * или использование подключения по умолчанию.
     *
     * Новое подключение заменяет подключение с идентификатором ""
     *
     * \return crOK - если подключение установлено
     */
    virtual ConnectionResult connectToDB() = 0;

    /*!
     * \brief Добавление файла БД SQLite
     * \param database - путь к файлу БД
     * \param title - Название подключения
     * \param comment - примечание
     */
    virtual void    addConnectionSQLite(QString databasePath,
                                        QString title) = 0;

    virtual int exec();
    virtual int exec(QWidget* parent);

    static IDBConnection* instance();
    static void        deleteInstance();

protected:
    static IDBConnection* _self;
    explicit IDBConnection(QWidget* parent);
    virtual ~IDBConnection();
};

#endif // IDBCONNECTION_H
