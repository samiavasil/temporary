
#include "qt/QPortIOSimulator.h"

QPortIOSimulator::QPortIOSimulator() {
  DEBUG("Create QPortIOSimulator");
  m_PortType = SIMULATOR_IO;
}

int64 QPortIOSimulator::bytesAvailable() {
}

int64 QPortIOSimulator::read(char * data, const int64 maxlen) {
}

int64 QPortIOSimulator::write(const char * data, const qint64 len) {
}

int QPortIOSimulator::open() {
}

int QPortIOSimulator::close() {
}

void QPortIOSimulator::readyReadSignal() {
}

