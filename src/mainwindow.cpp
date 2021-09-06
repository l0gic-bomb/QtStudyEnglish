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
    ui->word_view->setModel(_wordModel);


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
    if (selectedIds().size() == 1) {
        QString sql;
        long long currentId = selectedIds().first();
        QString where = " type_word_id = " + QString::number(currentId);

        if (currentId == 1) {

            sql = "SELECT * FROM verbs WHERE" + where;

            _wordModel->setColumns({{"form_1", "Форма 1"}, {"form_2", "Форма 2"}, {"form_3", "Форма 3"}});
            _wordModel->setQuery(sql);

            ui->word_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            ui->word_view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
            ui->word_view->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

        } else if (currentId == 2) {

            sql = "SELECT * FROM nouns WHERE " + where;
            _wordModel->setColumns({{"word", "Слово"}});
            _wordModel->setQuery(sql);
            ui->word_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        } else if (currentId == 3) {

            sql = "SELECT * FROM adverbs WHERE " + where;
            _wordModel->setColumns({{"word", "Слово"}});
            _wordModel->setQuery(sql);
            ui->word_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        } else if (currentId == 4) {

            sql = "SELECT * FROM adjectives WHERE " + where;
            _wordModel->setColumns({{"word", "Слово"}});
            _wordModel->setQuery(sql);
            ui->word_view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

        }

        qDebug() << sql;
    }


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
