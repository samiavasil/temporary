#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T14:50:54
#
#-------------------------------------------------

TARGET = qhexedit
TEMPLATE = lib

CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4) {
  QT+=widgets
}
INCLUDEPATH += $$PWD
DEFINES     += QHEDIT_LIB_LIBRARY

DESTDIR      = $$PWD/../../../../../bin/extlibs/
OBJECTS_DIR  = $$PWD/Build
MOC_DIR      = $$PWD/Build
RCC_DIR      = $$PWD/Build
UI_DIR       = $$PWD/Build

SOURCES += \
    ../xbytearray.cpp \
    ../qhexedit_p.cpp \
    ../qhexedit.cpp \
    ../commands.cpp

HEADERS +=\
    ../xbytearray.h \
    ../qhexedit_p.h \
    ../qhexedit.h \
    ../commands.h \
    qhedit_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE51A4A17
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = qhedit_lib.dll
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

OTHER_FILES += \
    ../license.txt
