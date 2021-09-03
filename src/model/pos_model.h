#ifndef POS_MODEL_H
#define POS_MODEL_H

/*!
  \brief   Модель для неизменяемых данных (частей речи)
  \author  Krymov A.O.
  \version 1.0
  \date    14.08.2021

  Модель предназначена ТОЛЬКО для чтения данных из
  таблицы БД

*/

#include <QAbstractItemModel>

class POS_Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    //! Конструктор
    explicit POS_Model(QObject* parent = nullptr);
    //! Деструктор
    virtual ~POS_Model() override = default;

    /*!
     * \brief setQuery Задает запрос к БД
     * \param query Запрос к БД
     */
    void setQuery(const QString& query) noexcept;

    /*!
     * \brief setColumns Задание колонок для представления
     * \param columns список пар <название колонки в БД, заголовок колонки в представлении>
     */
    void setColumns(const QList<QPair<QString, QString>>& columns) noexcept;

    /*!
     * \brief setContainer
     * \param container список данных из БД
     * \param columns   список пар <название колонки в БД, заголовок колонки в представлении>
     */
    void setContainer(const QList <QVariantHash> &container, const QList<QPair<QString, QString>> &columns) noexcept;

    /*!
     * \brief getRow берет хэш из списка БД
     * \param row номер строки в списке
     * \return  возвращает хэш
     */
    QVariantHash getRow(const int& row) const noexcept;

    //! Делаем запрос к БД, для взятия данных по таблице
    void select() noexcept;

    //! Реализация метода QAbstractItemModel::index()
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    //! Реализация метода QAbstractItemModel::parent()
    QModelIndex parent(const QModelIndex &) const override;
    //! Реализация метода QAbstractItemModel::rowCount()
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    //! Реализация метода QAbstractItemModel::columnCount()
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    //! Реализация метода QAbstractItemModel::data()
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    //! Реализация метода QAbstractItemModel::headerData()
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    //! Реализация метода QAbstractItemModel::flags()
    Qt::ItemFlags flags(const QModelIndex &index) const override;


protected:

    QString                     _query;       ///< Запрос к БД
    QStringList                 _columnOrder; ///< Список колонок
    QVariantHash                _titles;      ///< Заголовки хедера
    QList <QVariantHash>        _data;        ///< Список с данными из БД

    virtual QVariant displayRole(const QModelIndex &index) const noexcept;
    virtual QVariant userRole(const QModelIndex &index)    const noexcept;
};
#endif // POS_MODEL_H
