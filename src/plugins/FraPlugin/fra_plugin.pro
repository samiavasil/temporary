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
INCLUDEPATH += ../../extlibs/include
#INCLUDEPATH += ../../new_src
LIBS += -L../../../bin/extlibs -L../../../bin/libs  -lframe_work -lqwt

DEFINES += DEVICE_FACTORY_PLUGIN_LIBRARY

SOURCES += \
    frameworkinterface.cpp \
    QFraFrameWork.cpp \
    qtestcommand.cpp \
    QDataPlot.cpp

HEADERS += \
    frameworkinterface.h \
    QFraFrameWork.h \
    fra_plugin_global.h \
    qtestcommand.h \
    QDataPlot.h

CONFIG      += plugin





#LIBS += -L../../  -lfra

FORMS += \
    qdataplot.ui \
    qfra_frame_work_view.ui

RESOURCES += \
    proba.qrc
