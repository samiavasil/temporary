
#include "base/CPacketCollector.h"
#include "base/CPacket.h"
#include "base/CProtocolPackFactory.h"
#include "base/CPortIO.h"
#include "base/CFrameWork.h"

#include<stdio.h>//TODO DELL ME
CPacketCollector::CPacketCollector(CFrameWork * fWk) {
  m_fWork        = fWk;
  m_RecState    = COL_IDLE;
  m_TransState =TBD;
}

int CPacketCollector::receiveBytes() {
    int ret   = NO_ERR;                                                                                            
    int iteration;                                                                                                 
    int64 bytes_av;                                                                                                
    CPortIO *portIo ;                                                                                              
    CProtocolPackFactory * protocol;
    lockData();
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
            while( iteration > 0 ){                                                                                
                iteration--;                                                                                       
                switch(m_RecState){                                                                                
                case COL_IDLE:{                                                                                    
                    int offset = protocol->findPacketStart( getReceivedBytes(),getNumberOfReceivedBytes() );       
      			if( 0 <= offset /*TODO*/ ){                                                                      
      				removeReceivedBytes( offset );                                                               
      				m_RecState = COL_WAIT_FOR_HEADER;                                                            
      				iteration++;                                                                                 
      			}                                                                                                
      			break;                                                                                           
                }                                                                                                  
                case COL_WAIT_FOR_HEADER:{                                                                         
                                                                                                                   
                    if( protocol->getProtocolHeaderLenBits() <= (8*getNumberOfReceivedBytes())  )                  
                    {                                                                                              
                        m_RecState = COL_WAIT_FOR_PACK;                                                            
                        iteration++;                                                                               
                    }                                                                                              
                    break;                                                                                         
                }                                                                                                  
                case COL_WAIT_FOR_PACK:{                                                                           
                    if(  BITS_TO_BYTES_CEIL(protocol->getPacketLenFromData( getReceivedBytes() )) <=  getNumberOfReceivedBytes()  )
                    {                                                                                              
                        CPacket* packet = protocol->createPacketFromData( getReceivedBytes() );                    
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

