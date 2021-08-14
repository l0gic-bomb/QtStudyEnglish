QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/dbconnection/dbconnection.cpp \
    src/dbconnection/idbconnection.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/model/pos_model.cpp

HEADERS += \
    src/dbconnection/dbconnection.h \
    src/dbconnection/idbconnection.h \
    src/mainwindow.h \
    src/model/pos_model.h

FORMS += \
    src/dbconnection/dbconnection.ui \
    src/dbconnection/idbconnection.ui \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/res.qrc
