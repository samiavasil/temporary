
#include "qt/QSerialPortIO.h"

QSerialPortIO::QSerialPortIO(){
  DEBUG("Create QSerialPortIO");
  m_PortType = SERIALPORT_IO;
}

QSerialPortIO::~QSerialPortIO() {
  DEBUG("Destroy QPortIO");
}

int64 QSerialPortIO::bytesAvailable() {
  DEBUG("TODO: TBI ");
}

int64 QSerialPortIO::read(char * data, const int64 maxlen) {
  DEBUG("TODO: TBI ");
}

int64 QSerialPortIO::write(const char * data, const qint64 len) {
  DEBUG("TODO: TBI ");
}

int QSerialPortIO::open() {
  DEBUG("TODO: TBI ");
}

int QSerialPortIO::close() {
  DEBUG("TODO: TBI ");
}

void QSerialPortIO::readyReadSignal() {
  DEBUG("TODO: TBI ");
}

