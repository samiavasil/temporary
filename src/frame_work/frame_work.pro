#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:55:23
#
#-------------------------------------------------
DESTDIR = ../../bin/libs
TARGET = frame_work
TEMPLATE = lib
INCLUDEPATH += ../include/extlibs
DEFINES += FRAME_WORK_LIBRARY

OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build
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
    base/CCommand.cpp \
    base/CCommandExecutor.cpp \
    qt/QPacketCollector.cpp \
    qt/QCommandExecutor.cpp \
    qt/QCommand.cpp \
    base/CProtocolLoader.cpp \
    base/CProtocolPackFactory.cpp \
    qt/QProtocolPackFactory.cpp \
    qt/QProtocolLoader.cpp \
    base/CPacketCollector.cpp \
    base/CFrameWork.cpp \
    base/CPacket.cpp \
    qt/QFrameWork.cpp \
    base/CFrameWorkElementsFactory.cpp \
    qt/QFrameWorkElementsFactory.cpp \
    base/CPortIO.cpp \
    qt/QPluginLoaderExt.cpp \
    qt/QPluginDescriptor.cpp \
    qt/QPluginList.cpp \
    qt/QPluginObjectsInterface.cpp \
    base/CControlView.cpp \
    qt/QPortIO.cpp \
    base/CCreator.cpp \
    qt/QCreator.cpp \
    qt/PluginDescription.cpp \
    qt/qdbg.cpp \
    qt/QloggerInterface.cpp \
    qt/QSerialPortIO.cpp \
    base/CProtocolDb.cpp \
    qt/QProtocolDb.cpp

HEADERS +=\
    base/CCommand.h \
    base/CCommandExecutor.h \
    qt/QPacketCollector.h \
    qt/QCommandExecutor.h \
    qt/QCommand.h \
    base/global.h \
    base/CProtocolLoader.h \
    base/CProtocolPackFactory.h \
    qt/QProtocolPackFactory.h \
    qt/QProtocolLoader.h \
    qt/ProtoGen.h \
    base/CPacketCollector.h \
    base/CFrameWork.h \
    base/CPacket.h \
    qt/QFrameWork.h \
    base/CFrameWorkElementsFactory.h \
    qt/QFrameWorkElementsFactory.h \
    base/CPortIO.h \
    qt/QPluginLoaderExt.h \
    qt/QPluginDescriptor.h \
    qt/QPluginList.h \
    qt/interfaces.h \
    qt/frame_work_global.h \
    qt/QPluginObjectsInterface.h \
    base/CControlView.h \
    qt/QPortIO.h \
    base/CCreator.h \
    qt/QCreator.h \
    qt/PluginDescription.h \
    qt/qdbg.h \
    qt/QloggerInterface.h \
    base/debug.h \
    qt/QSerialPortIO.h \
    base/CProtocolDb.h \
    qt/QProtocolDb.h

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
    qt/serial_port.ui
