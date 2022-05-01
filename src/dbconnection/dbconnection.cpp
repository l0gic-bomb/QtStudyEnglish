#include "dbconnection.h"
#include "ui_dbconnection.h"

#include <QFileDialog>
#include <QDebug>

DBConnection::DBConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBConnection),
    mName("qtstudyenglish.sqlite")
{
    ui->setupUi(this);
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");

    connect(ui->btn_selectdb, &QToolButton::clicked,     this, &DBConnection::slSelectFileDB);
    connect(ui->btn_accept,   &QAbstractButton::clicked, this, &DBConnection::slAcceptChanges);
    connect(ui->btn_cancel,   &QAbstractButton::clicked, this, &DBConnection::slCancel);
    connect(ui->btn_create,   &QAbstractButton::clicked, this, &DBConnection::slCreateDB);
}

DBConnection::~DBConnection()
{
    delete ui;
}

void DBConnection::connectDB()
{
   // mDatabase.setDatabaseName(mPath);

  /* if (!mDatabase.open())
        qDebug() << "Не удалось подключиться";
    else
    {
        qDebug() << "Подключение успешно";
    }*/
}

QSqlDatabase DBConnection::getDatabase() const noexcept
{
    return mDatabase;
}

void DBConnection::slSelectFileDB()
{
    if (mPath.isEmpty()) {
        QString path = QFileDialog::getOpenFileName(this,
                                                    "Выбор базы данных",
                                                    mName,
                                                    "Файл БД SQLite (*.sqlite)",
                                                    nullptr);
        ui->le_path->setText(path);
        mPath = path;
    } else
        ui->le_path->setText(mPath);
    ui->rbtn_words->hide();
    ui->rbtn_words->setChecked(false);
}

void DBConnection::slAcceptChanges()
{
    connectDB();
    if (ui->rbtn_words->isChecked())
        createTable();
    this->close();
}

void DBConnection::slCancel()
{
    this->close();
}

void DBConnection::slCreateDB()
{
    const QDir dirDB = QDir::homePath() + QDir::separator() + "qtenglish";
    if (!dirDB.exists())
    {
        dirDB.mkdir(dirDB.path());
    }
    mPath = dirDB.path() + QDir::separator() + mName;
    QFile file(mPath);
    //if (file.exists()) //! TODO обработка перезаписи БД
     //   return;

    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        ui->le_path->setText(mPath);
        mDatabase.setDatabaseName(mPath);
        ui->rbtn_words->show();
        if (!mDatabase.open())
            qDebug() << "Не удалось подключиться";
        else
        {
            qDebug() << "Подключение успешно";
        }
        createTable();
    }
    else
    {
        qDebug() << "Не создан файл БД";
    }
    file.close();
}

void DBConnection::createTable()
{
    const QString pathToProject = PRO_FILE_PWD;
    QString pathToQuery = pathToProject + QDir::separator() + "queries" + QDir::separator() + "create_tables.sql";
    const QStringList queries = readQuery(pathToQuery);
    if (!queries.empty())
    {
        QSqlQuery query{mDatabase};
        for (const auto& strQuery : queries)
        {
            bool result = query.exec(strQuery);
            int tmp = 10;
        }
    }
    else
        return;
}

QStringList DBConnection::readQuery(const QString &path)
{
    QFile file(path);
    QByteArray data;
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Файл " << path << " недоступен для чтения или пуст";
        return QStringList();
    }
    data = file.readAll();
    QString tmp = data;
    QStringList queries;
    QString query;
    for (const auto& elem : data)
    {
        if (QString tmp{elem}; tmp == "\r" || tmp == "\n")
        {
            continue;
        }
        else if (elem != ';')
            query += elem;
        else
        {
            query += elem;
            queries.append(query);
            query.clear();
        }
    }
    file.close();
    return queries;
}


