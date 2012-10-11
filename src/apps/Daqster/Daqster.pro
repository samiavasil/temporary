#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:52:27
#
#-------------------------------------------------
QT       += core gui
TARGET   = Daqster
TEMPLATE = app
DESTDIR = ../../../bin
INCLUDEPATH += ../../frame_work
SOURCES += main.cpp\
        mainwindow.cpp \
    PluginList.cpp \
    QPluginLoaderExt.cpp \
    plugin_descriptor.cpp

HEADERS  += mainwindow.h \
    PluginList.h \
    QPluginLoaderExt.h \
    plugin_descriptor.h

FORMS    += mainwindow.ui \
    pluginlist.ui

LIBS += -L../../../bin/libs  -lframe_work

RESOURCES += \
    icons.qrc
