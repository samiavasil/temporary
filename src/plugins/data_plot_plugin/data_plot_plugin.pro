#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------
include(../../include/paths_cfg.pri)
DESTDIR      = $${PLUGINS_DEST_DIR}
QT          += core gui
TEMPLATE     = lib
INCLUDEPATH += ../
INCLUDEPATH += $${FRAMEWORK_INCLUDES_DIR}
INCLUDEPATH += $${EXT_LIBS_INCLUDES_DIR}
INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build
LIBS        += -L$${EXT_LIBS_DIR} -L$${LIBS_DIR}

TEMPLATE     = lib
CONFIG      += plugin
DEFINES     += BUILD_AVAILABLE_PLUGIN

LIBS        += -lframe_work -lqwt
TARGET   = DataPlotPlugin

greaterThan(QT_MAJOR_VERSION, 4) {
QT += printsupport
}

SOURCES += \
    DataPlotWorkInterface.cpp \
    QwtPlotExt.cpp \
    QwtPlotConfigurator.cpp \
    QDataPlot.cpp \
    CurveConfigurator.cpp \
    CurveConfigurationMenu.cpp

HEADERS += \
    DataPlotWorkInterface.h \
    QwtPlotExt.h \
    QwtPlotConfigurator.h \
    QDataPlot.h \
    CurveConfigurator.h \
    CurveConfigurationMenu.h


#LIBS += -L../../  -lfra

FORMS += \
    QwtPlotConfigurator.ui \
    qdataplot.ui \
    CurveConfigurator.ui

RESOURCES += \
    proba.qrc \
    proba.qrc


