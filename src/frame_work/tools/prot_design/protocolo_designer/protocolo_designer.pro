#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T16:27:57
#
#-------------------------------------------------

QT       += core gui
QT       += sql
TARGET = protocolo_designer
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}


SOURCES += main.cpp\
        mainwindow.cpp \
    qsqlconnectiondialog.cpp \
    sqldatamanager.cpp \
    docwriter.cpp \
    generator.cpp \
    output_writer.cpp \
    data_manager.cpp

HEADERS  += mainwindow.h \
    qsqlconnectiondialog.h \
    sqldatamanager.h \
    docwriter.h \
    generator.h \
    output_writer.h \
    prot_types.h \
    data_manager.h

FORMS    += mainwindow.ui \
    qsqlconnectiondialog.ui

RESOURCES += \
    resources.qrc
