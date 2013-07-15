#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:52:27
#
#-------------------------------------------------
QT       += core gui

OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build


TARGET   = Daqster
TEMPLATE = app
DESTDIR = ../../../bin
INCLUDEPATH += ../../frame_work
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

CONFIG      += designer

LIBS += -L../../../bin/libs  -lframe_work -lQtDesignerComponents -lQtDesigner



RESOURCES += \
    icons.qrc

FORMS += \
    mainwindow.ui
