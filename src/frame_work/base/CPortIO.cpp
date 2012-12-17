
#include "base/CPortIO.h"

CPortIO::CPortIO() {
  m_PortType = UNDEFINED_IO;
}

CPortIO::~CPortIO() {
}

CPortIO::portIo_type CPortIO::type() {
  return m_PortType;
}

