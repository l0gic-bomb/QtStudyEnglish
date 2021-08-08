QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/dbconnection/connectioneditdialog.cpp \
    src/dbconnection/dataconnection.cpp \
    src/dbconnection/dbconnection.cpp \
    src/dbconnection/dbconnectionmodel.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    src/dbconnection/connectioneditdialog.h \
    src/dbconnection/dataconnection.h \
    src/dbconnection/dbconnection.h \
    src/dbconnection/dbconnectionmodel.h \
    src/mainwindow.h

FORMS += \
    src/dbconnection/connectioneditdialog.ui \
    src/dbconnection/dbconnection.ui \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res.qrc
