#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------

DESTDIR = ../../../bin/plugins
QT       += core gui
TARGET = DeviceFabriquePlugin
TEMPLATE = lib

INCLUDEPATH += ../../frame_work
INCLUDEPATH += ../../new_src
DEFINES += DEVICEFABRIQUEPLUGIN_LIBRARY

SOURCES += \
    frameworkinterface.cpp \
    QFraFrameWork.cpp

HEADERS += \
    frameworkinterface.h \
    QFraFrameWork.h \
    fra_plugin_global.h

CONFIG      += plugin





#LIBS += -L../../  -lfra

FORMS += \
    qframeworkview.ui
