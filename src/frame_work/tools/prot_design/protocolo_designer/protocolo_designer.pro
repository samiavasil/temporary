#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T16:27:57
#
#-------------------------------------------------

QT       += core gui
QT       += sql
TARGET = protocolo_designer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qsqlconnectiondialog.cpp \
    sqldatamanager.cpp \
    docwriter.cpp

HEADERS  += mainwindow.h \
    qsqlconnectiondialog.h \
    sqldatamanager.h \
    docwriter.h

FORMS    += mainwindow.ui \
    qsqlconnectiondialog.ui

RESOURCES += \
    resources.qrc
