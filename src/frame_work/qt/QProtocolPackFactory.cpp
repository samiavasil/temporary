
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"

QProtocolPackFactory::QProtocolPackFactory(QProtocolLoader * pLoader) :CProtocolPackFactory(pLoader){
}

void QProtocolPackFactory::clearProtDefinitions() {
  m_packMap.clear();
  m_msgMap.clear(); 
}

int QProtocolPackFactory::addPacket(const pack_id_t id) {
  int ret = NO_ERR;                                                    
  if( ( id < PKT_ID_INVALID )&&(false == m_packMap.contains( id )) ){  
      m_packMap.insert( id,QList< msg_id_t>() );                       
  }                                                                    
  else{                                                                
      DEBUG("Packet Id[%d] already exist.",id);                        
      ret = WRONG_PARAMS;                                              
  }                                                                    
  return ret;                                                          
}

int QProtocolPackFactory::addMessage(const msg_id_t id, int len) {
  int ret = NO_ERR;                                                  
  if( ( id < MSG_ID_INVALID )&&(false == m_msgMap.contains( id )) ){ 
      msg_desc_t descMsg;                                            
      descMsg.msgID  = id;                                           
      descMsg.bitLen = len;                                          
      m_msgMap.insert( id, descMsg );                                
  }                                                                  
  else{                                                              
      DEBUG("Message Id[%d] already exist.",id);                     
      ret = WRONG_PARAMS;                                            
  }                                                                  
  return ret;                                                        
}

int QProtocolPackFactory::addMessageToPacket(const pack_id_t packID, const msg_id_t msgID) {
  int ret = NO_ERR;                                                                                        
  if( ( packID < PKT_ID_INVALID )&&( msgID < MSG_ID_INVALID )&&(true == m_packMap.contains( packID ))  ){  
      if( false == m_packMap[packID].contains(msgID) ){                                                    
          m_packMap[packID].append( msgID );                                                               
      }                                                                                                    
      else{                                                                                                
          DEBUG( "Message [%d] was already added to Packet Id[%d]",msgID, packID );                        
          ret = WRONG_PARAMS;                                                                              
      }                                                                                                    
  }                                                                                                        
  else{                                                                                                    
      DEBUG( "Packet Id[%d] not defined",packID );                                                         
      ret = WRONG_PARAMS;                                                                                  
  }                                                                                                        
  return ret;                                                                                                                                                                             
}

int QProtocolPackFactory::getMessageBitLen(msg_id_t msgId, int * msgLen) {
  int ret = NO_ERR;                                               
  if( ( msgId < MSG_ID_INVALID ) && ( 0 != msgLen ) ){            
      if( false != m_msgMap.contains( msgId ) ){                  
          *msgLen = m_msgMap[ msgId ].bitLen;                     
      }                                                           
      else{                                                       
          DEBUG("Message Id[%d] already exist.",msgId);           
          *msgLen = 0;                                            
          ret     = WRONG_PARAMS;                                 
      }                                                           
  }                                                               
  else{                                                           
      DEBUG("Invalid Message Id[%d]",msgId);                      
      ret = WRONG_PARAMS;                                         
  }                                                               
}

int QProtocolPackFactory::getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) {
  int ret = NO_ERR;                                                                         
  int i, msgPos = 0;                                                                        
  if( ( packId < PKT_ID_INVALID )&&( msgId < MSG_ID_INVALID ) && ( 0 != offset ) ){         
      int msgIdx = m_packMap[packId].indexOf( msgId );                                      
      if( 0 <= msgIdx ){                                                                    
          QList<msg_id_t> listPackMsg = m_packMap[packId];                                  
          for( i=0 ; i < msgIdx;i++){                                                       
              if( m_msgMap.contains( listPackMsg[i] ) ){     
                DOBAWI OBRABOTKA ZA RAZMER -1
                  msgPos +=  m_msgMap[ listPackMsg[i] ].bitLen;                             
              }                                                                             
              else{                                                                         
                  msgPos = -1;                                                              
                  DEBUG("Wrong Message Id[%d] for packet Id[%d].",listPackMsg[i],packId );  
                  ret = SOME_ERROR;                                                         
              }                                                                             
          }                                                                                 
      }                                                                                     
      else{                                                                                 
          DEBUG("Message Id[%d] already exist.",msgId);                                     
          msgPos  = -1;                                                                     
          ret     = WRONG_PARAMS;                                                           
      }                                                                                     
      if( 0 <= msgPos ){                                                                    
         *offset = msgPos;                                                                  
      }                                                                                     
  }                                                                                         
  else{                                                                                     
      DEBUG("Invalid Input parameters");                                                    
      ret = WRONG_PARAMS;                                                                   
  }                                                                                         
}

int QProtocolPackFactory::getPacketLenFromData(const u8 * data) {
}

pack_id_t QProtocolPackFactory::getPacketTypeFromData(const u8 * data) {
}

int QProtocolPackFactory::getMessage(msg_id_t id, const u8 * data) {
}

int QProtocolPackFactory::setMessage(const msg_id_t msgId, const u8 * data) {
}

int QProtocolPackFactory::checkPacketConsistency(const u8 * data) {
}

int QProtocolPackFactory::findPacketStart() {
}

int QProtocolPackFactory::packetLen(const pack_id_t packId) {
}

int QProtocolPackFactory::getPacketMessagesNumber(const pack_id_t & packId) {
}

int QProtocolPackFactory::getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) {
}

