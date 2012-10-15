
#include "base/CProtocolPackFactory.h"
#include "base/CProtocolLoader.h"
#include "base/CPacket.h"

CProtocolPackFactory::CProtocolPackFactory(CProtocolLoader * pLoader) {
  pLoader = pLoader;
  m_hDrLenBits       = 0;
  m_postFixLenBits   = 0;    
  m_maxPacketSize    = 0;    
}

int CProtocolPackFactory::attachProtocolLoader(CProtocolLoader * pLoader) {
    int ret = NO_ERR;
    if(  pLoader ) { 
       clearProtDefinitions();  
       pLoader->loadProtocolDefinition(this);   
    } 
    else{
       ret = WRONG_PARAMS;
   }
   return ret;
}

CPacket* CProtocolPackFactory::createPacket(const pack_id_t packId) {
    CPacket * packet = NULL;
  
    if( PKT_ID_INVALID < packId ){                                                                                  
        return packet;                                                                                              
    }                                                                                                               
    int payloadLenBits=0;                                                                                           
    if( NO_ERR == packetPayloadBitLen(packId, &payloadLenBits )){                                                   
        packet = new CPacket( packId,payloadLenBits + getProtocolHeaderLenBits() + getProtocolPostFixLenBits() );   
        int num;                                                                                                    
        if( ( NO_ERR == getPacketMessagesNumber( packId,&num ) )&&( 0 < num ) ){                                    
            msg_id_t msgArr[num];
            if( NO_ERR == getPacketMessagesId( packId, msgArr, num ) ){                                             
                const u8 *data;                                                                                     
                for( int i=0; i < num; i++ ){                                                                       
                    if( NO_ERR != getMessage( msgArr[i], &data ) ){
                        CRITICAL( "Wrong Message Id[%d] for Packet Id[%d]",msgArr[i] , packId );
                        delete packet;
                        packet = NULL;
                        break;
                    }
                    if( NO_ERR != setPacketMessage( packet,msgArr[i], data ) ){
                        CRITICAL( "Can't set Message with Id[%d] for Packet with Id[%d]",msgArr[i] , packId );
                        delete packet;
                        packet = NULL;
                        break;
                    }
                }                                                                                                   
            }                                                                                                       
  
        }                                                                                                           
    }                                                                                                               
    return packet;            
}

CPacket* CProtocolPackFactory::createPacketFromData(const u8 * data) {
    CPacket * packet = NULL;                                                                 
    if( NULL == data ){                                                                      
        return packet;                                                                       
    }                                                                                        
  
    packet = new CPacket( getPacketTypeFromData(data), getPacketLenFromData(data) );
    if( NO_ERR != packet->setData( data ) ){
        CRITICAL( "Can't create packet from data"  );
        delete packet;
        packet = NULL;
    }
    if( NO_ERR != checkPacketConsistency( packet ) ){
        delete packet;
        packet = NULL;
        CRITICAL( "Can't create packet: Data inconsistent."  );                              
    }                                                                                        
    return packet;                      
}

int CProtocolPackFactory::setPacketMessage(CPacket * packet, msg_id_t msgId, const u8 * data) {
    int ret = WRONG_PARAMS;
    int msgLen;                                                                 
    int offset;                                                                 
    if( ( NULL == packet )||( NULL == data ) ){                                 
        return ret;
    }                                                                           
    ret =  getMessageBitOffsetInPack( packet->packType() ,msgId , &offset );    
    if( NO_ERR == ret ){                                                        
        ret = getMessageBitLen( msgId, &msgLen );                               
        if( NO_ERR == ret ){                                                    
            ret = packet->setBits( offset, msgLen, data );                      
        }
        else{
            CRITICAL("Can't set Message bits in packet for msgID[%d]",msgId);
        }
    }
    else{
        CRITICAL("Can't get Message offset in packet for msgID[%d]",msgId);
    }
    return ret;
}

int CProtocolPackFactory::getPacketMessage(CPacket * packet, msg_id_t msgId, u8 * retData) {
  int ret;                                                                  
  int msgLen;                                                               
  int offset;                                                               
  if( ( NULL == packet )||( NULL == retData ) ){                            
      return WRONG_PARAMS;                                                  
  }                                                                         
  ret =  getMessageBitOffsetInPack( msgId, packet->packType(), &offset );   
  if( NO_ERR == ret ){                                                      
      ret = getMessageBitLen( msgId, &msgLen );                             
      if( NO_ERR == ret ){                                                  
          ret = packet->getBits( offset, msgLen, retData );                 
      }                                                                     
  }                                                                         
  return ret;                                                               
}

int CProtocolPackFactory::getMaxPacketLen() {
  return m_maxPacketSize;
}

void CProtocolPackFactory::setMaxPacketLen(int max_size) {
  m_maxPacketSize = max_size;
}

int CProtocolPackFactory::getPacketHeader(CPacket * packet, u8 * header) {
  if( ( NULL == packet )||( NULL == header ) ){                         
      return WRONG_PARAMS;                                              
  }                                                                     
  return packet->getBits( 0, getProtocolHeaderLenBits(), header );      
}

int CProtocolPackFactory::getPacketPostFix(CPacket * packet, u8 * retPostFix) {
  int ret =  WRONG_PARAMS;                                                     
  int offset;                                                                  
  if( ( NULL == packet )||( NULL == retPostFix ) ){                            
      return ret;                                                              
  }                                                                            
  offset = packet->packLenBits() - getProtocolPostFixLenBits();                
  if( getProtocolHeaderLenBits() < offset ){                                   
     ret = packet->getBits( offset, getProtocolPostFixLenBits(), retPostFix ); 
  }                                                                            
  else{                                                                        
     CRITICAL("Not correct packet semantic");                                  
     ret = WRONG_DATA;                                                         
  }                                                                            
  return ret;                                                                  
}

