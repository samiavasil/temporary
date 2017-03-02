#include "qt/QPacketCollector.h"
#include "base/CPortIO.h"
#include "base/CPacket.h"
#include "base/CProtocolPackFactory.h"

#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"


QPacketCollector::QPacketCollector(CPortIO * port, CProtocolPackFactory * protocol, QObject * parent):
    QObject(parent),m_Mutex(QMutex::Recursive) {
    DEBUG << "Create QPacketCollector";
    m_PortIo   = port;
    m_Protocol = protocol;
    if( !(port && protocol) )
    {
        DEBUG << "ERROR!!!!!!: Port or Protocol NULL pointer";
    }
    m_RecState    = COL_IDLE;
    m_TransState  = TBD;
}

QPacketCollector::~QPacketCollector() {
  DEBUG << "Destroy QPacketCollector";
  while( m_PacketsList.count( ) ){
      delete m_PacketsList.takeFirst();
  }
}

bool QPacketCollector::isChained() {
  return m_PortIo && m_Protocol;
}

int QPacketCollector::setProtocolFactory( CProtocolPackFactory * protocol ){
    m_Protocol = protocol;
}

int QPacketCollector::setPort( CPortIO * port ){
    m_PortIo = port;
}

int QPacketCollector::receiveBytes() {
      int ret   = NO_ERR;
      int iteration;
      int64 bytes_av;

      lockData();

      if( isChained() ){
          u8 data[m_Protocol->getMaxPacketLen()];
          while( (bytes_av = m_PortIo->bytesAvailable()) ){
              m_PortIo->read( (char*)data, bytes_av );
              appendReceivedBytes( data, bytes_av );
              iteration = 1;
              while( iteration > 0 ){
                  iteration--;
                  switch(m_RecState){
                  case COL_IDLE:{
                      int offset = m_Protocol->findPacketStart( getReceivedBytes(),getNumberOfReceivedBytes() );
                    if( 0 <= offset /*TODO*/ ){
                        removeReceivedBytes( offset );
                        m_RecState = COL_WAIT_FOR_HEADER;
                        iteration++;
                    }
                    break;
                  }
                  case COL_WAIT_FOR_HEADER:{

                      if( m_Protocol->getProtocolHeaderLenBits() <= (8*getNumberOfReceivedBytes())  )
                      {
                          m_RecState = COL_WAIT_FOR_PACK;
                          iteration++;
                      }
                      break;
                  }
                  case COL_WAIT_FOR_PACK:{
                      if(  BITS_TO_BYTES_CEIL(m_Protocol->getPacketLenFromData( getReceivedBytes() )) <=  getNumberOfReceivedBytes()  )
                      {
                          CPacket* packet = m_Protocol->createPacketFromData( getReceivedBytes() );
                          if( ( NULL == packet )||( NO_ERR != collectPacket( packet ) ) ){
                              /*Packet not correct or packet start isn't calculate corectly.
                         Remove only one byte and try to find packet start again. Someting as
                         packet start search procedure*/
                              removeReceivedBytes( 1 );
                          }
                          else{
                              removeReceivedBytes( packet->packLenBytes() );
                          }
                          m_RecState = COL_IDLE;
                      }
                      break;
                  }
                  default:{
                  }
                  }
              }
          }
      }
      else{
          ret = NULL_POINTER;
      }
      unlockData();
      return ret;
}


int QPacketCollector::getRecPacket() {
  DEBUG << "TODO:Not implemented";
  return 0;
}

int QPacketCollector::transmitPacket(CPacket * packet) {
    int ret = WRONG_PARAMS;                                                     
  
    if( packet && isChained() ){
        ret = m_Protocol->addPacketHeader(packet);
        if( NO_ERR == ret )
        {
           ret = m_Protocol->addPacketPostFix(packet);
           if( NO_ERR == ret )
           {
             ret = m_PortIo->write((const char *) packet->data(),packet->packLenBytes());
             DEBUG << "m_PortIo->write "<< ret << " bytes number.";
           }
           else{
               DEBUG << "ERROR: Can't addPacketPostFix";
           }
        }
        else{
            DEBUG << "ERROR: Can't addPacketHeader ";
        }
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
      if( packet ){
          fprintf( stderr," Receive Packet[%d]: Data is:\n",packet->packType() );
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

