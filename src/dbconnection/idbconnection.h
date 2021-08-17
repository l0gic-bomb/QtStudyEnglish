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

    enum Result
    {
        OK = 0,
        Error = 1,
        PathNotExists = 2
    };
    Q_ENUM(Result);

    virtual Result connectDB() = 0;
    virtual void   addConnection(const QString& databasePath, const QString& title) = 0;
    virtual bool   getState() const noexcept = 0;

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
