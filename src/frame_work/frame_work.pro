#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:55:23
#
#-------------------------------------------------
DESTDIR = ../../bin/libs
TARGET = frame_work
TEMPLATE = lib

DEFINES += FRAME_WORK_LIBRARY

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
    qt/QSerialPortIO.cpp \
    qt/QPortIOSimulator.cpp \
    qt/QPluginLoaderExt.cpp \
    qt/QPluginDescriptor.cpp \
    qt/QPluginList.cpp \
    qt/QPluginObjectsInterface.cpp

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
    qt/QSerialPortIO.h \
    qt/QPortIOSimulator.h \
    qt/QPluginLoaderExt.h \
    qt/QPluginDescriptor.h \
    qt/QPluginList.h \
    qt/interfaces.h \
    qt/frame_work_global.h \
    qt/QPluginObjectsInterface.h

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
    qt/pluginlist.ui
