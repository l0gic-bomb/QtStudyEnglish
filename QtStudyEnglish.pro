QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    src/dbconnection/dbconnection.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model/pos_model.cpp \
    src/model/word_model.cpp

HEADERS += \
    src/dbconnection/dbconnection.h \
    src/mainwindow.h \
    src/model/pos_model.h \
    src/model/word_model.h

FORMS += \
    src/dbconnection/dbconnection.ui \
    src/mainwindow.ui

RESOURCES += \
    src/res.qrc
