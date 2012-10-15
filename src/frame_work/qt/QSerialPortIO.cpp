
#include "qt/QSerialPortIO.h"

QSerialPortIO::QSerialPortIO() {
    DEBUG("Create QSerialPortIO");
    m_PortType = SERIALPORT_IO;
}

QSerialPortIO::~QSerialPortIO() {
    DEBUG("Destroy QPortIO");
}

int64 QSerialPortIO::bytesAvailable() {
    DEBUG("TODO: TBI ");
    return 0;
}

int64 QSerialPortIO::read(char * data, const int64 maxlen) {
    DEBUG("TODO: TBI %x %lld",(unsigned int)data,maxlen);
    return 0;
}

int64 QSerialPortIO::write(const char * data, const qint64 len) {
    DEBUG("TODO: TBI %x %lld",(unsigned int)data,len);
    return 0;
}

int QSerialPortIO::open() {
    DEBUG("TODO: TBI ");
    return 0;
}

int QSerialPortIO::close() {
    DEBUG("TODO: TBI ");
    return 0;
}

void QSerialPortIO::readyReadSignal() {
    DEBUG("TODO: TBI ");
}

