#include "base/CPacketCollector.h"
#include "base/CPacket.h"
#include "base/CProtocolPackFactory.h"
#include "base/CPortIO.h"


//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

CPacketCollector::CPacketCollector(CPortIO * port, CProtocolPackFactory * protocol) {
  m_PortIo   = port;
  m_Protocol = protocol;
  if( !(port && protocol) )
  {
     DEBUG << "ERROR!!!!!!: Port or Protocol NULL pointer";
  }
  m_RecState    = COL_IDLE;
  m_TransState  = TBD;
}

CPacketCollector::~CPacketCollector() {
}

bool CPacketCollector::isChained() {
  return m_PortIo && m_Protocol;
}

int CPacketCollector::receiveBytes() {
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

