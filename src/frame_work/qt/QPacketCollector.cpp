
#include "qt/QPacketCollector.h"
#include "base/CFrameWork.h"
#include "base/CPacket.h"

QPacketCollector::QPacketCollector(CFrameWork * cFwk):CPacketCollector( cFwk){
  DEBUG("Create QPacketCollector");
}

QPacketCollector::~QPacketCollector() {
  DEBUG("Destroy QPacketCollector");
}

int QPacketCollector::getRecPacket() {
  DEBUG("TODO:Not implemented");
}

int QPacketCollector::getRecPacketNum() {
  DEBUG("TODO:Not implemented");
}

void QPacketCollector::receivedBytesSlot() {
  receiveBytes();
}

int QPacketCollector::appendReceivedBytes(const u8 * data, const int64 len) {
  int ret = NO_ERR;                               
  if( data ){                                     
      m_Data.append( (const char*) data, len );   
  }                                               
  else{                                           
      ret = WRONG_PARAMS;                         
  }                                               
  return ret;                                     
}

int QPacketCollector::collectPacket(CPacket * packet) {
  int ret = NO_ERR;                                                 
  if( packet ){                                                     
      DEBUG("Append Packet pointer: TODO free pointer after usage");
      m_PacketsList.append( packet );                               
  }                                                                 
  else{                                                             
      ret = WRONG_PARAMS;                                           
  }                                                                 
  return ret;                                                       
}

int QPacketCollector::getNumberOfReceivedBytes() {
  return m_Data.size();
}

const u8* QPacketCollector::getReceivedBytes() {
  return (const u8*)m_Data.constData();
}

void QPacketCollector::removeReceivedBytes(int byteNum) {
  m_Data.remove(0,byteNum);
}

