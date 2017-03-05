#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:55:23
#
#-------------------------------------------------
DESTDIR = ../../bin/libs
#CONFIG += debug_and_release
TARGET = frame_work
#win32|mac:!wince*:!win32-msvc:!macx-xcode:CONFIG += debug_and_release build_all
win32 {
    # On Windows you can't mix release and debug libraries.
    # The designer is built in release mode. If you like to use it
    # you need a release version. For your own application development you
    # might need a debug version.
    # Enable debug_and_release + build_all if you want to build both.

    CONFIG           += debug_and_release
    CONFIG           += build_all
    CONFIG(debug, debug|release) {
        TARGET = $${TARGET}d
    }
}


TEMPLATE = lib
INCLUDEPATH += ../include/extlibs
DEFINES += FRAME_WORK_LIBRARY
OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}
# This is an example for building and using qextserialport.
#
# When using the qextserialport, all you need is to add following line
# in your .pro file:
include(../extlibs/qextserialport-1.2beta2/src/qextserialport.pri)
#
# uncomment the following line if you want to use qextserialport as library
# QEXTSERIALPORT_LIBRARY = yes

# uncomment the following line too if you want to use it as static library
QEXTSERIALPORT_STATIC = yes

# comment following line if you always want to enable "udev" under linux
#QEXTSERIALPORT_WITH_UDEV = yes

SOURCES += \
    base/CRegFactory.cpp \
    qt/QPacketCollector.cpp \
    qt/QCommandExecutor.cpp \
    qt/QCommand.cpp \
    qt/QProtocolPackFactory.cpp \
    qt/QProtocolLoader.cpp \
    qt/QFrameWork.cpp \
    qt/QPluginLoaderExt.cpp \
    qt/QPluginList.cpp \
    qt/QPluginObjectsInterface.cpp \
    qt/QPortIO.cpp \
    qt/QCreator.cpp \
    qt/PluginDescription.cpp \
    qt/qdbg.cpp \
    qt/QSerialPortIO.cpp \
    qt/QProtocolDb.cpp \
    qt/QRegFactory.cpp \
    qt/QPluginViewProperty.cpp \
    qt/QPluginListWidget.cpp \
    qt/QPluginSelectionView.cpp \
    qt/QPluginFactory.cpp \
    qt/QPluginFilter.cpp \
    qt/QLoggerInterface.cpp \
    qt/QTestFrameWorkElementsFactory.cpp \
    qt/QDataPlot.cpp \
    qt/QPacket.cpp

HEADERS +=\
    base/global.h \
    base/debug.h \
    base/CRegFactory.h \
    base/build_cfg.h \
    qt/QPacketCollector.h \
    qt/QCommandExecutor.h \
    qt/QCommand.h \
    qt/QProtocolPackFactory.h \
    qt/QProtocolLoader.h \
    qt/ProtoGen.h \
    qt/QFrameWork.h \
    qt/QPluginLoaderExt.h \
    qt/QPluginList.h \
    qt/interfaces.h \
    qt/QPluginObjectsInterface.h \
    qt/QPortIO.h \
    qt/QCreator.h \
    qt/PluginDescription.h \
    qt/qdbg.h \
    qt/QSerialPortIO.h \
    qt/QProtocolDb.h \
    qt/QRegFactory.h \
    qt/QPluginViewProperty.h \
    qt/QPluginListWidget.h \
    qt/QPluginSelectionView.h \
    qt/QPluginFactory.h \
    qt/QPluginFilter.h \
    qt/QLoggerInterface.h \
    qt/QTestFrameWorkElementsFactory.h \
    qt/QDataPlot.h \
    qt/QFrameWorkElementsFactory.h \
    qt/QPacket.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xEC538F15
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = frame_work.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    qt/pluginlist.ui \
    qt/serial_port.ui \
    qt/QPluginViewProperty.ui \
    qt/QPluginSelectionView.ui
