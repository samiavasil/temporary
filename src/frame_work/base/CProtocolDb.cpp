#include "CProtocolDb.h"

CProtocolDb::CProtocolDb()
{

}

int CProtocolDb::getProtocolHeaderLenBits() const {
  return m_hDrLenBits;
}

void CProtocolDb::setProtocolHeaderLenBits(int lenBits) {
  m_hDrLenBits = lenBits;
}

int CProtocolDb::getProtocolPostFixLenBits() const {
  return m_postFixLenBits;
}

void CProtocolDb::setProtocolPostFixLenBits(int lenBits) {
  m_postFixLenBits = lenBits;
}

int CProtocolDb::getMaxPacketLen() {
  return m_maxPacketSize;
}

void CProtocolDb::setMaxPacketLen(int max_size) {
  m_maxPacketSize = max_size;
}
