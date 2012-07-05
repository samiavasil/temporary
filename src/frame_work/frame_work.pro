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
    QFrameWork.cpp \
    base/CCommand.cpp \
    base/CCommandExecutor.cpp \
    qt/QPacketCollector.cpp \
    qt/QCommandExecutor.cpp \
    qt/QCommand.cpp

HEADERS +=\
        frame_work_global.h \
    interfaces.h \
    QFrameWork.h \
    base/CCommand.h \
    base/CCommandExecutor.h \
    qt/QPacketCollector.h \
    qt/QCommandExecutor.h \
    qt/QCommand.h \
    base/global.h

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
