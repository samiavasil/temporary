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
    QFrameWork.cpp

HEADERS +=\
        frame_work_global.h \
    interfaces.h \
    QFrameWork.h

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
