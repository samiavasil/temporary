#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------
include(../../include/paths_cfg.pri)
DESTDIR      = $${PLUGINS_DEST_DIR}
QT          += core gui
TEMPLATE     = lib

QMAKE_CXXFLAGS      +=  -g3 -O0

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
greaterThan(QT_MAJOR_VERSION, 4) {
QT+=designer
QT+=uitools
}
else{
CONFIG      += designer
CONFIG += uitools
}
DEFINES     += BUILD_AVAILABLE_PLUGIN

#-lQt5DesignerComponents -lQt5Designer

TARGET   = VDesignerPlugin

SOURCES += \
    VDesignerInterface.cpp \
    DesignerFrameWork.cpp \
    DesignerCreator.cpp

HEADERS += \
    VDesignerInterface.h \
    DesignerFrameWork.h \
    DesignerCreator.h

FORMS += \
    desinger.ui

RESOURCES +=

OTHER_FILES += \
    VDesignerInterface.json

win32 {
    # On Windows you can't mix release and debug libraries.
    # The designer is built in release mode. If you like to use it
    # you need a release version. For your own application development you
    # might need a debug version.
    # Enable debug_and_release + build_all if you want to build both.

#    CONFIG           += debug_and_release
#    CONFIG           += build_all
    CONFIG(debug, debug|release) {
        TARGET = $${TARGET}d
        LIBS        += -l$${FRAMEWORK_LIB_NAME}d -lQt5DesignerComponentsd
    }
}
else
{
    LIBS        += -l$${FRAMEWORK_LIB_NAME} -lQt5DesignerComponents
}
