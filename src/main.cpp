#include "mainwindow.h"

#include <QApplication>
#include "dbconnection/dbconnection.h"
#include <QStyleFactory>

/*! TODO
 * Класс для подключения к БД (+)
 * Модель для частей речи (+)
 * Модель для сортировки
 * Модель для слов, с закрашениванием уровня
 * Добавление, удаление слов. Класс запросов к БД
 * Диалог для проверки слов
 * Грамматические тесты
*/

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow w;
    w.show();

    return a.exec();
}
