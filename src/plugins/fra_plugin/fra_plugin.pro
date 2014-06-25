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
TARGET       = FraPlugin




SOURCES  += \
    qtestcommand.cpp \
    FraFrameWorkInterface.cpp \
    QFraCreator.cpp \
    QFraFrameWork.cpp \
    QPortsIoView.cpp

HEADERS += \
    qtestcommand.h \
    FraFrameWorkInterface.h \
    QFraCreator.h \
    QFraFrameWork.h \
    QPortsIoView.h \
    QPortsIoView.h


FORMS += \
    qfra_frame_work_view.ui \
    QPortsIoView.ui

RESOURCES += \
    proba.qrc



