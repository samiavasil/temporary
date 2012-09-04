
#include "base/CPacketCollector.h"
#include "base/CPacket.h"
#include "base/CProtocolPackFactory.h"
#include "base/CPortIO.h"
#include "base/CFrameWork.h"

CPacketCollector::CPacketCollector(CFrameWork * fWk) {
  m_fWork = fWk;
}

int CPacketCollector::receiveBytes() {
  int ret   = NO_ERR;                                                                                     
  int iteration;                                                                                          
  int64 bytes_av;                                                                                         
  CPortIO *portIo ;                                                                                       
  CProtocolPackFactory * protocol;                                                                        
  if( NULL != m_fWork ){                                                                                  
      portIo   = m_fWork->getPortIO();                                                                    
      protocol = m_fWork->getProtocol();                                                                  
  }                                                                                                       
  else{                                                                                                   
      return NULL_POINTER;                                                                                
  }                                                                                                       
  if( portIo && protocol ){                                                                               
      u8 data[protocol->getMaxPacketLen()];                                                               
      while( (bytes_av = portIo->bytesAvailable()) ){                                                     
          portIo->read( (char*)data, bytes_av );                                                          
          appendReceivedBytes( data, bytes_av );                                                          
          iteration = 1;                                                                                  
          while( iteration > 0 )                                                                          
              iteration--;                                                                                
          switch(state){                                                                                  
          case COL_IDLE:{                                                                                 
              if( protocol->findPacketStart()/*TODO*/ ){                                                  
                  state = COL_WAIT_FOR_PACK;                                                              
                  iteration++;                                                                            
              }                                                                                           
              break;                                                                                      
          }                                                                                               
          case COL_WAIT_FOR_HEADER:{                                                                      
                                                                                                          
              if( protocol->getProtocolHeaderLen( ) <= getNumberOfReceivedBytes()  )                      
              {                                                                                           
                  state = COL_WAIT_FOR_PACK;                                                              
                  iteration++;                                                                            
              }                                                                                           
              break;                                                                                      
          }                                                                                               
          case COL_WAIT_FOR_PACK:{                                                                        
              if(  protocol->getPacketLenFromData( getReceivedBytes() ) <=  getNumberOfReceivedBytes()  ) 
              {                                                                                           
                  CPacket* packet = protocol->createPacketFromData( getReceivedBytes() );                 
                  if( ( NULL == packet )||( NO_ERR != collectPacket( packet ) ) ){                        
  				     /*Packet not correct or packet start isn't calculate corectly.                       
                       Remove only one byte and try to find packet start again. Someting as               
                       packet start search procedure*/                                                    
                       removeReceivedBytes( 1 );                                                          
  				  }				                                                                          
      			  state = COL_IDLE;                                                                       
              }                                                                                           
              break;                                                                                      
          }                                                                                               
          default:{                                                                                       
          }                                                                                               
          }                                                                                               
      }                                                                                                   
  }                                                                                                       
  else{                                                                                                   
      ret = NULL_POINTER;                                                                                 
  }                                                                                                       
  return ret;                                                                                             
}

