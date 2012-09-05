
#include "base/CProtocolPackFactory.h"
#include "base/CProtocolLoader.h"
#include "base/CPacket.h"

CProtocolPackFactory::CProtocolPackFactory(CProtocolLoader * pLoader) {
  m_hDrSize       = 0;                         
  m_postFixSize   = 0;                         
  m_maxPacketSize = 0;                         
                                         
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
  int packLen=0;                                                                                
  if( NO_ERR == packetLen(packId, &packLen )){                                                  
      packet = new CPacket( packId,packLen, getProtocolHeaderLen(), getProtocolPostFixLen() );  
      int num;                                                                                  
      if( ( NO_ERR == getPacketMessagesNumber( packId,&num ) )&&( 0 < num ) ){                  
          msg_id_t msgArr[num];                                                                 
          if( NO_ERR == getPacketMessagesId( packId, msgArr, num ) ){                           
              const u8 *data;                                                                   
              for( int i=0; i < num; i++ ){                                                     
                  if( NO_ERR == getMessage( msgArr[i], data ) ){                                
                      setPacketMessage( packet,msgArr[i], data );                               
                  }                                                                             
                  else{                                                                         
                      CRITICAL( "Wrong Message Id[%d] for Packet Id[%d]",msgArr[i] , packId );  
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
  if( checkPacketConsistency( data ) ){                                               
    packet = new CPacket( getPacketTypeFromData(data), getPacketLenFromData(data),    
                          getProtocolHeaderLen()     , getProtocolPostFixLen()    );  
    if( NO_ERR != packet->setData( data ) ){                                          
        CRITICAL( "Can't create packet from data"  );               
        delete packet;                                                                
        packet = NULL;                                                                
    }                                                                                 
  }                                                                                   
  else{                                                                               
      CRITICAL( "Can't create packet: Data inconsistent."  );   
  }                                                                                   
  return packet;                                                                      
}

int CProtocolPackFactory::setPacketMessage(CPacket * packet, msg_id_t msgId, const u8 * data) {
  int ret;                                                                    
  int msgLen;                                                                 
  int offset;                                                                 
  if( ( NULL == packet )||( NULL == data ) ){                                 
      return WRONG_PARAMS;                                                    
  }                                                                           
  ret =  getMessageBitOffsetInPack( packet->packType() ,msgId , &offset );    
  if( NO_ERR == ret ){                                                        
      ret = getMessageBitLen( msgId, &msgLen );                               
      if( NO_ERR == ret ){                                                    
          ret = packet->setBits( offset, msgLen, data );                      
      }                                                                       
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
  return packet->getBits( 0, getProtocolHeaderLen(), header );      
}

int CProtocolPackFactory::setPacketHeader(CPacket * packet, u8 * header) {
  if( ( NULL == packet )||( NULL == header ) ){                
      return WRONG_PARAMS;                                     
  }                                                            
  return packet->setBits( 0, getProtocolHeaderLen(), header ); 
}

int CProtocolPackFactory::setPacketPostFix(CPacket * packet, u8 * postfix) {
  int ret =  WRONG_PARAMS;                                                
  int offset;                                                             
  if( ( NULL == packet )||( NULL == postfix ) ){                          
      return WRONG_PARAMS;                                                
  }                                                                       
  offset = packet->packLen() - getProtocolPostFixLen();                   
  if( getProtocolHeaderLen() < offset ){                                  
     ret = packet->setBits( offset, getProtocolPostFixLen(), postfix );   
  }                                                                       
  else{                                                                   
     CRITICAL("Not correct packet semantic");                             
     ret = WRONG_DATA;                                                    
  }                                                                       
  return ret;                                                             
}

int CProtocolPackFactory::getPacketPostFix(CPacket * packet, u8 * retPostFix) {
  int ret =  WRONG_PARAMS;                                                  
  int offset;                                                               
  if( ( NULL == packet )||( NULL == retPostFix ) ){                         
      return ret;                                                           
  }                                                                         
  offset = packet->packLen() - getProtocolPostFixLen();                     
  if( getProtocolHeaderLen() < offset ){                                    
     ret = packet->getBits( offset, getProtocolPostFixLen(), retPostFix );  
  }                                                                         
  else{                                                                     
     CRITICAL("Not correct packet semantic");                               
     ret = WRONG_DATA;                                                      
  }                                                                         
  return ret;                                                               
}

