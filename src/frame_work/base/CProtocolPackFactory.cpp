
#include "base/CProtocolPackFactory.h"
#include "base/CProtocolLoader.h"
#include "base/CPacket.h"
#include "base/CProtocolDb.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

CProtocolPackFactory::CProtocolPackFactory(CProtocolLoader * pLoader) {
  pLoader = pLoader;
}

CProtocolPackFactory::CProtocolPackFactory( CProtocolDb * protDB ):m_pDB( protDB ){

}

int CProtocolPackFactory::attachProtocolLoader(CProtocolLoader * pLoader) {
    int ret = NO_ERR;
    if(  pLoader ) {
       ret = pLoader->loadProtocolDefinition( m_pDB );

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
    if( NO_ERR == m_pDB->packetPayloadBitLen(packId, &payloadLenBits )){
        packet = new CPacket( packId,payloadLenBits + m_pDB->getProtocolHeaderLenBits() + m_pDB->getProtocolPostFixLenBits() );
        int num;                                                                                                    
        if( ( NO_ERR == m_pDB->getPacketMessagesNumber( packId,&num ) )&&( 0 < num ) ){
            msg_id_t msgArr[num];
            if( NO_ERR == m_pDB->getPacketMessagesId( packId, msgArr, num ) ){
                const u8 *data;                                                                                     
                for( int i=0; i < num; i++ ){                                                                       
                    if( NO_ERR != m_pDB->getMessage( msgArr[i], &data ) ){
                        CRITICAL << "Wrong Message Id[" << msgArr[i] << "] for Packet Id[" << packId << "]";
                        delete packet;
                        packet = NULL;
                        break;
                    }
                    if( NO_ERR != setPacketMessage( packet,msgArr[i], data ) ){
                        CRITICAL << "Can't set Message with Id[" << msgArr[i]
                                 << "] for Packet with Id[" << packId << "]";
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
        CRITICAL <<  "Can't create packet from data";
        delete packet;
        packet = NULL;
    }
    if( NO_ERR != checkPacketConsistency( packet ) ){
        delete packet;
        packet = NULL;
        CRITICAL <<  "Can't create packet: Data inconsistent.";
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
    ret =  m_pDB->getMessageBitOffsetInPack( packet->packType() ,msgId , &offset );
    if( NO_ERR == ret ){                                                        
        ret = m_pDB->getMessageBitLen( msgId, &msgLen );
        if( NO_ERR == ret ){                                                    
            ret = packet->setBits( offset, msgLen, data );                      
        }
        else{
            CRITICAL << "Can't set Message bits in packet for msgID["<< msgId << "]";
        }
    }
    else{
        CRITICAL << "Can't get Message offset in packet for msgID[" << msgId << "]";
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
  ret =  m_pDB->getMessageBitOffsetInPack( msgId, packet->packType(), &offset );
  if( NO_ERR == ret ){                                                      
      ret = m_pDB->getMessageBitLen( msgId, &msgLen );
      if( NO_ERR == ret ){                                                  
          ret = packet->getBits( offset, msgLen, retData );                 
      }                                                                     
  }                                                                         
  return ret;                                                               
}

int CProtocolPackFactory::getPacketHeader(CPacket * packet, u8 * header) {
  if( ( NULL == packet )||( NULL == header ) ){                         
      return WRONG_PARAMS;                                              
  }                                                                     
  return packet->getBits( 0, m_pDB->getProtocolHeaderLenBits(), header );
}

int CProtocolPackFactory::getPacketPostFix(CPacket * packet, u8 * retPostFix) {
  int ret =  WRONG_PARAMS;                                                     
  int offset;                                                                  
  if( ( NULL == packet )||( NULL == retPostFix ) ){                            
      return ret;                                                              
  }                                                                            
  offset = packet->packLenBits() - m_pDB->getProtocolPostFixLenBits();
  if( m_pDB->getProtocolHeaderLenBits() < offset ){
     ret = packet->getBits( offset, m_pDB->getProtocolPostFixLenBits(), retPostFix );
  }                                                                            
  else{                                                                        
     CRITICAL << "Not correct packet semantic";
     ret = WRONG_DATA;                                                         
  }                                                                            
  return ret;                                                                  
}

CProtocolPackFactory::~CProtocolPackFactory() {
}

