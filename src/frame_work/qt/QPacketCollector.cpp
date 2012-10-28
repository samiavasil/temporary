
#include "qt/QPacketCollector.h"
#include "base/CPortIO.h"
#include "base/CPacket.h"
#include "base/CFrameWork.h"

QPacketCollector::QPacketCollector(CFrameWork * cFwk):CPacketCollector( cFwk){
  DEBUG("Create QPacketCollector");
}

QPacketCollector::~QPacketCollector() {
  DEBUG("Destroy QPacketCollector");
  while( m_PacketsList.count( ) ){
      delete m_PacketsList.takeAt(0);
  }
}

int QPacketCollector::getRecPacket() {
  DEBUG("TODO:Not implemented");
  return 0;
}

int QPacketCollector::transmitPacket(CPacket * packet) {
  int ret = WRONG_PARAMS;                                                     
  CPortIO* port = m_fWork->getPortIO();                                       
  CProtocolPackFactory*protocol = m_fWork->getProtocol();                     
  if( port&&protocol ){                                                       
      protocol->addPacketHeader(packet);                                      
      protocol->addPacketPostFix(packet);                                     
      ret = port->write((const char *) packet->data(),packet->packLenBytes());
  }                                                                           
  return ret;                                                                 
}

int QPacketCollector::getRecPacketNum() {
  DEBUG("TODO:Not implemented");
  return 0;
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
#include<stdio.h>//DEL ME
int QPacketCollector::collectPacket(CPacket * packet) {
  int ret = NO_ERR;                                                                                          
  static int a;                                                                                              
  if( packet ){                                                                                              
      DEBUG("Append Packet pointer: TODO free pointer after usage  PackId[%d] num %d",packet->packType(),a); 
      if( 1 ){//packet ){
          const u8*data = packet->data();
          for( int i=0;i < packet->packLenBytes();i++ ){
              fprintf(stderr," %02x",data[i]);
          }
          fprintf(stderr,"\n\n");
      }
      a++;
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

void QPacketCollector::lockData() {
  m_Mutex.lock();
}

void QPacketCollector::unlockData() {
  m_Mutex.unlock();
}

const u8* QPacketCollector::getReceivedBytes() {
  return (const u8*)m_Data.constData();
}

void QPacketCollector::removeReceivedBytes(int byteNum) {
  m_Data.remove(0,byteNum);
}

