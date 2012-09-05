
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"

QProtocolPackFactory::QProtocolPackFactory(QProtocolLoader * pLoader) :CProtocolPackFactory(pLoader){
  DEBUG("Create QProtocolPackFactory");
  if(  attachProtocolLoader(pLoader) ) {                                                             
      DEBUG("!!!ProtocolLoader isn't attached to ProtocolPackFactory: Use attachProtocolLoader()");  
  }                                                                                                  
}

QProtocolPackFactory::~QProtocolPackFactory() {
}

void QProtocolPackFactory::clearProtDefinitions() {
  m_packMap.clear();                               
  QMapIterator<msg_id_t , msg_desc_t> i(m_msgMap); 
  while (i.hasNext()) {                            
      i.next();                                    
      delete [] (i.value().data);                  
  }                                                
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
      descMsg.data   = new u8[ BITS_TO_BYTES_CEIL( len ) ]; 
      memset(  descMsg.data, 0, BITS_TO_BYTES_CEIL( len ) );
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

int QProtocolPackFactory::getMessage(msg_id_t id, const u8 * data) {
  int ret = NO_ERR;
  if( ( 0 != data ) && ( true == m_msgMap.contains( id ) ) ){   
      data = m_msgMap[id].data;                                 
  }                                                             
  else{                                                         
      ret = WRONG_PARAMS;                                       
  }                                                             
  return ret;
}

int QProtocolPackFactory::setMessage(const msg_id_t msgId, const u8 * data) {
  int ret = NO_ERR;                                                                        
  if( ( 0 != data ) && ( true == m_msgMap.contains( msgId ) ) ){                           
      mempcpy( m_msgMap[msgId].data, data, BITS_TO_BYTES_CEIL( m_msgMap[msgId].bitLen ) ); 
  }                                                                                        
  else{                                                                                    
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
  return ret;                                            
}

int QProtocolPackFactory::getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) {
  int ret = NO_ERR;                                                                                                                                     
  int i, msgPos = 0;                                                                                                                                    
  if(  ( packId < PKT_ID_INVALID )&&( msgId < MSG_ID_INVALID ) && ( 0 != offset ) && m_packMap.contains(packId) ){                                                                     
      int msgIdx = m_packMap[packId].indexOf( msgId );                                                                                                  
      if( 0 <= msgIdx ){                                                                                                                                
          QList<msg_id_t> listPackMsg = m_packMap[packId];                                                                                              
          for( i=0 ; i < msgIdx;i++){                                                                                                                   
              if( m_msgMap.contains( listPackMsg[i] ) ){                                                                                                
                  if( 0 < m_msgMap[ listPackMsg[i] ].bitLen ){                                                                                          
                      msgPos +=  m_msgMap[ listPackMsg[i] ].bitLen;                                                                                     
                  }                                                                                                                                     
                  else{                                                                                                                                 
                      if( 0 == m_msgMap[ listPackMsg[i] ].bitLen ){                                                                                     
                          DEBUG("Someting Wrong!!!: Size equal to 0 for MessageId[%d] in PacketId[%d]",listPackMsg[i] ,packId);                         
                      }                                                                                                                                 
                      else{                                                                                                                             
                          msgPos = -1;                                                                                                                  
                          DEBUG("Can't'find MessageId[%d] offset for packet Id[%d]: maybe packet max size is reached ==> Last MessageId[%d] size=%d",   
                                msgId, packId, listPackMsg[i], m_msgMap[ listPackMsg[i] ].bitLen );                                                     
                          ret = SOME_ERROR;                                                                                                             
                          break;                                                                                                                        
                      }                                                                                                                                 
                  }                                                                                                                                     
              }                                                                                                                                         
              else{                                                                                                                                     
                  msgPos = -1;                                                                                                                          
                  DEBUG("Wrong Message Id[%d] for packetId[%d].",listPackMsg[i],packId );                                                               
                  ret = SOME_ERROR;                                                                                                                     
                  break;                                                                                                                                
              }                                                                                                                                         
          }                                                                                                                                             
      }                                                                                                                                                 
      else{                                                                                                                                             
          DEBUG("Message Id[%d] doesn't' exist in packetId[%d]",msgId,packId);                                                                          
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
  return ret;
}

int QProtocolPackFactory::getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) {
}

int QProtocolPackFactory::getPacketMessagesNumber(const pack_id_t packId, int * msgNum) {
  int ret = NO_ERR;                                
  if( ( 0 != msgNum )&&(packId < PKT_ID_INVALID) ){
      *msgNum = m_packMap[packId].count();         
  }                                                
  else{                                            
       ret = WRONG_PARAMS;                         
  }                                                
  return ret;                                      
}

int QProtocolPackFactory::packetLen(const pack_id_t packId, int * packLenBits) {
   int ret = NO_ERR;                                                                                
   int i;                                                                                           
   if( ( packId < PKT_ID_INVALID )&&( m_packMap.contains(packId) ) ){                               
       int msgNum = m_packMap[packId].count();                                                      
       *packLenBits = 0;                                                                            
       for( i=0 ; i < msgNum; i++ ){                                                                
           if( m_msgMap.contains( m_packMap[packId].value(i) ) ){                                   
               if( 0 < m_msgMap[ m_packMap[packId].value(i) ].bitLen ){                             
                   *packLenBits += m_msgMap[ m_packMap[packId].value(i) ].bitLen;                   
               }                                                                                    
               else{                                                                                
                   *packLenBits = m_maxPacketSize;                                                  
               }                                                                                    
           }                                                                                        
           else{                                                                                    
               *packLenBits = 0;                                                                    
               DEBUG("Wrong Message Id[%d] for packetId[%d].",m_packMap[packId].value(i),packId );  
               ret = SOME_ERROR;                                                                    
               break;                                                                               
           }                                                                                        
       }                                                                                            
       if( *packLenBits > m_maxPacketSize){                                                         
           DEBUG("!!!! Packet Size > maxPacketSize for packetId[%d].", packId );                    
           *packLenBits = 0;                                                                        
           ret = SOME_ERROR;                                                                        
       }                                                                                            
   }                                                                                                
   else{                                                                                            
       DEBUG("Invalid Input parameters");                                                           
       ret = WRONG_PARAMS;                                                                          
   }                                                                                                                                                        
   return ret;                                                                                      
}

int QProtocolPackFactory::checkPacketConsistency(const u8 * data) {
  return NO_ERR;
}

int QProtocolPackFactory::findPacketStart() {
  return 0;
}

int QProtocolPackFactory::getPacketLenFromData(const u8 * data) {
}

pack_id_t QProtocolPackFactory::getPacketTypeFromData(const u8 * data) {
}

