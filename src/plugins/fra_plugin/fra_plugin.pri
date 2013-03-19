#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------

INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build

TARGET = DeviceFabriquePlugin
LIBS += -lframe_work -lqwt

DEFINES += DEVICE_FACTORY_PLUGIN_LIBRARY

SOURCES += \
    QFraFrameWork.cpp \
    qtestcommand.cpp \
    QDataPlot.cpp \
    FraFrameWorkInterface.cpp \
    QwtPlotExt.cpp \
    QwtPlotConfigurator.cpp \
    CurveConfigurator.cpp \
    CurveConfigurationMenu.cpp

HEADERS += \
    QFraFrameWork.h \
    fra_plugin_global.h \
    qtestcommand.h \
    QDataPlot.h \
    FraFrameWorkInterface.h \
    QwtPlotExt.h \
    QwtPlotConfigurator.h \
    CurveConfigurator.h \
    CurveConfigurationMenu.h






#LIBS += -L../../  -lfra

FORMS += \
    qdataplot.ui \
    qfra_frame_work_view.ui \
    QwtPlotConfigurator.ui \
    CurveConfigurator.ui

RESOURCES += \
    proba.qrc
