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
    ui->rbtn_words->hide();
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
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(mPath);

    if (!mDatabase.open())
        qDebug() << "Не удалось подключиться";
    else
        qDebug() << "Подключение успешно";
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
}

void DBConnection::slAcceptChanges()
{
    connectDB();
    if (ui->rbtn_words->windowState())
    this->close();
}

void DBConnection::slCancel()
{
    this->close();
}

void DBConnection::slCreateDB()
{
    QDir dirDB = QDir::homePath() + QDir::separator() + "qtenglish";
    if (!dirDB.exists())
    {
        dirDB.mkdir(dirDB.path());
    }
    QString pathToDB = dirDB.path() + QDir::separator() + mName;
    QFile file(pathToDB);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        ui->le_path->setText(pathToDB);
        ui->rbtn_words->show();
        createTable();
        file.close();
    }
    else
    {
        qDebug() << "Не создан файл БД";
    }
}

bool DBConnection::createTable()
{

    //! Записать запросы в отдельный файл
    //! Запрсы создания таблиц
    //! Запросы базовые данные
    //!
}


