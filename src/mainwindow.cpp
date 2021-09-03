#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _connection    = new DBConnection(this);
    _typeOfSpeech  = new POS_Model(this);
    _wordModel     = new Word_Model(this);
    _sortModel     = new QSortFilterProxyModel(this);

    _sortModel->setSourceModel(_typeOfSpeech);

    ui->pos_view->setModel(_sortModel);
    ui->right_view->setModel(_wordModel);


    connect(ui->btn_connection, &QToolButton::clicked, this, &MainWindow::slConnectionDB);
    connect(ui->pos_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::slSelectionItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slConnectionDB()
{
    if (!_connection->exec()) {
        _typeOfSpeech->setColumns({{"part_of_speech", "Часть речи"}});
        QString sql = "SELECT * FROM type_word ORDER BY id";
        qDebug() << sql;
        _typeOfSpeech->setQuery(sql);
        ui->pos_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }
}

void MainWindow::slSelectionItem()
{

}

QList<long long> MainWindow::selectedIds()
{
    QList<long long> ids;
    QModelIndexList listIndexes = ui->pos_view->selectionModel()->selectedRows();
    if (listIndexes.isEmpty())
        return ids;

    for (int i = 0; i < listIndexes.size(); ++i)
        ids << getRecord(listIndexes.at(i)).value("id").toLongLong();
    return ids;
}

QVariantHash MainWindow::getRecord(const QModelIndex &index)
{
    return _typeOfSpeech->getRow(_sortModel->mapToSource(index).row());
}
