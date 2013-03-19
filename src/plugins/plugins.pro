DESTDIR = ../../bin/plugins
QT       += core gui
TEMPLATE = lib
INCLUDEPATH += $$PWD
INCLUDEPATH += ../frame_work
INCLUDEPATH += ../include/extlibs
LIBS += -L../../bin/extlibs -L../../bin/libs
CONFIG      += plugin
include(./fra_plugin/fra_plugin.pri)

HEADERS += \
    plugin_global.h
