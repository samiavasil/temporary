#include "qt/QPacketCollector.h"
#include "base/CPortIO.h"
#include "base/CPacket.h"
#include "base/CProtocolPackFactory.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"


QPacketCollector::QPacketCollector(CPortIO * port, CProtocolPackFactory * protocol, QObject * parent):QObject(parent),CPacketCollector( port,protocol ) {
  DEBUG << "Create QPacketCollector";
}

QPacketCollector::~QPacketCollector() {
  DEBUG << "Destroy QPacketCollector";
  while( m_PacketsList.count( ) ){
      delete m_PacketsList.takeFirst();
  }
}

int QPacketCollector::getRecPacket() {
  DEBUG << "TODO:Not implemented";
  return 0;
}

int QPacketCollector::transmitPacket(CPacket * packet) {
    int ret = WRONG_PARAMS;                                                     
  
    if( packet && isChained() ){
        m_Protocol->addPacketHeader(packet);
        m_Protocol->addPacketPostFix(packet);
        ret = m_PortIo->write((const char *) packet->data(),packet->packLenBytes());
    }                                                                           
    return ret;                                                                
}

int QPacketCollector::getRecPacketNum() {
  DEBUG << "TODO:Not implemented";
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

int QPacketCollector::collectPacket(CPacket * packet) {
  int ret = NO_ERR;                                                                                          
  static int a;                                                                                              
  if( packet ){                                                                                              
      DEBUG << "Append Packet pointer: TODO free pointer after usage  PackId["<< packet->packType()<< "] num " << a;
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

