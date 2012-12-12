#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29T11:52:27
#
#-------------------------------------------------
QT       += core gui


# This is an example for building and using qextserialport.
#
# When using the qextserialport, all you need is to add following line
# in your .pro file:
include(../../extlibs/qextserialport/src/qextserialport.pri)
#
# uncomment the following line if you want to use qextserialport as library
# QEXTSERIALPORT_LIBRARY = yes

# uncomment the following line too if you want to use it as static library
QEXTSERIALPORT_STATIC = yes

# comment following line if you always want to enable "udev" under linux
#QEXTSERIALPORT_WITH_UDEV = yes

TARGET   = Daqster
TEMPLATE = app
DESTDIR = ../../../bin
INCLUDEPATH += ../../frame_work
SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -L../../../bin/libs  -lframe_work
CCFLAG += -E
RESOURCES += \
    icons.qrc
