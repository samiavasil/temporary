#-------------------------------------------------
#
# Project created by QtCreator 2012-06-21T13:34:25
#
#-------------------------------------------------
ENABLE_DIAGRAM=

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


greaterThan(QT_MAJOR_VERSION, 4) {
QT += printsupport
}


DEFINES     += BUILD_AVAILABLE_PLUGIN
TARGET   = QDiagramPlugin


#contains( ENABLE_DIAGRAM, 1 ){
SOURCES += \
    QDiagramPluginInterface.cpp \
    diagramtextitem.cpp \
    diagramscene.cpp \
    diagrampathitem.cpp \
    DiagMainWindow.cpp \
    vdiagramitem.cpp \
    vdiagramdrawitem.cpp \
    diagramitem.cpp \
    diagramdrawitem.cpp

HEADERS += \
    QDiagramPluginInterface.h \
    diagramtextitem.h \
    diagramscene.h \
    diagrampathitem.h \
    DiagMainWindow.h \
    vdiagramitem.h \
    vdiagramdrawitem.h \
    items_type_names.h \
    diagramdrawitem.h \
    diagramitem.h
#}

#LIBS += -L../../  -lfra

FORMS +=

RESOURCES += \
    qdiagram.qrc

OTHER_FILES += \
    QDiagramPluginInterface.json

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
        LIBS        += -l$${FRAMEWORK_LIB_NAME}d
    }
}
else
{
    LIBS        += -l$${FRAMEWORK_LIB_NAME}
}

