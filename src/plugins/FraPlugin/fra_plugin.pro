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
    QFraFrameWork.cpp \
    qtestcommand.cpp \
    QDataPlot.cpp \
    FraFrameWorkInterface.cpp \
    QwtPlotExt.cpp \
    QwtPlotConfigurator.cpp \
    CurveConfigurator.cpp

HEADERS += \
    QFraFrameWork.h \
    fra_plugin_global.h \
    qtestcommand.h \
    QDataPlot.h \
    FraFrameWorkInterface.h \
    QwtPlotExt.h \
    QwtPlotConfigurator.h \
    CurveConfigurator.h

CONFIG      += plugin





#LIBS += -L../../  -lfra

FORMS += \
    qdataplot.ui \
    qfra_frame_work_view.ui \
    QwtPlotConfigurator.ui \
    CurveConfigurator.ui

RESOURCES += \
    proba.qrc
