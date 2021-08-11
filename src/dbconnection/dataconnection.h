#ifndef DATACONNECTION_H
#define DATACONNECTION_H

#include <QObject>

struct ConnectionParams
{
    int _port;
    int _defaultPort;

    QString _host;
    QString _dbName;
    QString _userName;
    QString _password;
    QString _dbType;
    QString _defaultHost;
    QString _defaultDbName;
    QString _defaultDbType;
    QString _errorText;
};

class DataConnection : public QObject
{
    Q_OBJECT

public:
    ~DataConnection();

    static DataConnection *instance();

    int port() const;
    QString host() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString dbType() const;

    void setHost(const QString& host);
    void setDatabaseName(const QString& dbName);
    void setUserName(const QString& userName);
    void setPassword(const QString& password);
    void setDbType(const QString& dbType);

    void loadSettings();

    QString errorText();

private:
    explicit DataConnection(QObject *parent = nullptr);
    static DataConnection* _instance;
    ConnectionParams* _params;
};


#endif // DATACONNECTION_H
