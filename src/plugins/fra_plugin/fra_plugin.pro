#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------

DESTDIR = ../../../bin/plugins
QT       += core gui
TEMPLATE = lib
INCLUDEPATH += ../
INCLUDEPATH += ../../frame_work
INCLUDEPATH += ../../include/extlibs
CONFIG      += plugin
LIBS += -L../../../bin/extlibs -L../../../bin/libs
include(./fra_plugin.pri)


