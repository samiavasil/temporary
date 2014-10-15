#include "QProtocolDb.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

void QProtocolDb::clearProtDefinitions() {
      m_packMap.clear();
      QMapIterator<msg_id_t , msg_desc_t> i(m_msgMap);
      while (i.hasNext()) {
          i.next();
          delete [] (i.value().data);
      }
      m_msgMap.clear();
}

int QProtocolDb::addPacket(const pack_id_t id) {
   int ret = NO_ERR;
      if( ( id < PKT_ID_INVALID )&&(false == m_packMap.contains( id )) ){
          m_packMap.insert( id,QList< msg_id_t>() );
      }
      else{
          DEBUG << "Packet Id["<< id <<"] already exist.";
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::isTherePacketId(const pack_id_t id){
    return m_packMap.contains(id);
}

int QProtocolDb::addMessage(const msg_id_t id, int len) {
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
          DEBUG << "Message Id["<< id << "] already exist.";
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::getMessage(msg_id_t id, const u8 ** data) {
      int ret = NO_ERR;
      if( ( 0 != data ) && ( true == m_msgMap.contains( id ) ) ){
          *data = m_msgMap[id].data;
      }
      else{
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::setMessage(const msg_id_t msgId, const u8 * data) {
      int ret = NO_ERR;
      if( ( 0 != data ) && ( true == m_msgMap.contains( msgId ) ) ){
          int num_bytes = BITS_TO_BYTES_CEIL( m_msgMap[msgId].bitLen);
          int last_bit  = m_msgMap[msgId].bitLen%8;
          mempcpy( m_msgMap[msgId].data, data, num_bytes );
          if( last_bit )
          {
              m_msgMap[msgId].data[0] &= MASK_OFF_LEN( 0,last_bit );
          }
      }
      else{
          ret = WRONG_PARAMS;
      }

      return ret;
}

int QProtocolDb::getMessageBitLen(msg_id_t msgId, int * msgLen) {
      int ret = NO_ERR;
      if( ( msgId < MSG_ID_INVALID ) && ( 0 != msgLen ) ){
          if( false != m_msgMap.contains( msgId ) ){
              *msgLen = m_msgMap[ msgId ].bitLen;
          }
          else{
              DEBUG << "Message Id[" << msgId << "] already exist.";
              *msgLen = 0;
              ret     = WRONG_PARAMS;
          }
      }
      else{
          DEBUG << "Invalid Message Id[" << msgId << "]";
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) {
      int ret = NO_ERR;
      int i, msgPos = m_hDrLenBits;
      if(  ( packId < PKT_ID_INVALID )&&( msgId < MSG_ID_INVALID ) && ( 0 != offset ) && m_packMap.contains(packId) ){
          int msgIdx = m_packMap[packId].indexOf( msgId );
          if( 0 <= msgIdx ){
              //QList<msg_id_t> listPackMsg = m_packMap.value(packId,QList<msg_id_t>());
              if( !m_packMap.value(packId,QList<msg_id_t>()).isEmpty() ){
                  for( i=0 ; i < msgIdx;i++){
                      if( m_msgMap.contains( m_packMap.value(packId,QList<msg_id_t>())[i] ) ){
                          if( 0 < m_msgMap[ m_packMap.value(packId,QList<msg_id_t>())[i] ].bitLen ){
                              msgPos +=  m_msgMap[ m_packMap.value(packId,QList<msg_id_t>())[i] ].bitLen;
                          }
                          else{
                              if( 0 == m_msgMap[ m_packMap.value(packId,QList<msg_id_t>())[i] ].bitLen ){
                                  DEBUG << "Someting Wrong!!!: Size equal to 0 for MessageId["
                                        <<  m_packMap.value(packId,QList<msg_id_t>())[i]
                                        << "] in PacketId["<<packId << "]";
                              }
                              else{
                                  msgPos = -1;
                                  DEBUG << "Can't'find MessageId[" << msgId << "]offset for packet Id[" << packId
                                        << "]: maybe packet max size is reached ==> Last MessageId["
                                        << m_packMap.value(packId,QList<msg_id_t>())[i]
                                        << "] size=" << m_msgMap[ m_packMap.value(packId,QList<msg_id_t>())[i] ].bitLen;
                                  ret = SOME_ERROR;
                                  break;
                              }
                          }
                      }
                      else{
                          msgPos = -1;
                          DEBUG << "Wrong Message Id[" << m_packMap.value(packId,QList<msg_id_t>())[i]
                                << "] for packetId[" << packId << "].";
                          ret = SOME_ERROR;
                          break;
                      }
                  }
              }
              else{
                  msgPos = -1;
                  CRITICAL << "Mising Packet ID[ " << packId << "] in message map";
                  ret = SOME_ERROR;
              }
          }
          else{
              DEBUG << "Message Id[" << msgId << "] doesn't' exist in packetId[" << packId << "]";
              msgPos  = -1;
              ret     = WRONG_PARAMS;
          }
          if( m_hDrLenBits <= msgPos ){
              *offset = msgPos;
          }
      }
      else{
          DEBUG << "Invalid Input parameters";
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) {
      int ret = WRONG_PARAMS;
      if( ( 0 != msgArr )&&(packId < PKT_ID_INVALID) ){
          QList<msg_id_t> packMsgs =  m_packMap.value( packId, QList<msg_id_t>() );
          if( !packMsgs.isEmpty() ){
              if( num > packMsgs.count() ){
                  num = packMsgs.count();
                  DEBUG << "!!!Return only first " <<  num << " messages from packet[" << packId << "]";
              }
              for( int i=0;i < num;i++ ){
                  msgArr[i] = packMsgs.value(i,MSG_ID_INVALID);
              }
              ret = NO_ERR;
          }
      }
      return ret;
}

int QProtocolDb::getPacketMessagesNumber(const pack_id_t packId, int * msgNum) {
      int ret = NO_ERR;
      if( ( 0 != msgNum )&&(packId < PKT_ID_INVALID) ){
          *msgNum = m_packMap[packId].count();
      }
      else{
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::addMessageToPacket(const pack_id_t packID, const msg_id_t msgID) {
      int ret = NO_ERR;
      if( ( packID < PKT_ID_INVALID )&&( msgID < MSG_ID_INVALID )&&(true == m_packMap.contains( packID ))  ){
          if( false == m_packMap[packID].contains(msgID) ){
              m_packMap[packID].append( msgID );
          }
          else{
              DEBUG <<  "Message ["<< msgID << "] was already added to Packet Id[" << packID << "]";
              ret = WRONG_PARAMS;
          }
      }
      else{
          DEBUG <<  "Packet Id[" << packID << "] not defined";
          ret = WRONG_PARAMS;
      }
      return ret;
}

int QProtocolDb::packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits) {
  int ret = NO_ERR;
  int i;
  if( ( packId < PKT_ID_INVALID )&&( m_packMap.contains(packId) ) ){
      msg_id_t msgId;
      int msgNum = m_packMap[packId].count();
      *payloadLenBits = 0;
      for( i=0 ; i < msgNum; i++ ){
          msgId = m_packMap[packId].value(i);
          if( m_msgMap.contains( msgId ) ){
              if( 0 < m_msgMap[ msgId ].bitLen ){
                  *payloadLenBits += m_msgMap[ msgId ].bitLen;
              }
              else{
                  *payloadLenBits = m_maxPacketSize;
              }
          }
          else{
              *payloadLenBits = 0;
              DEBUG << "Wrong Message Id[" << msgId <<"] for packetId[" << packId << "]";
              ret = SOME_ERROR;
              break;
          }
      }
      /*TODO - can be configure option*/
      #define ALLIGN_PAYLOAD_TO_BYTE
      #if  defined( ALLIGN_PAYLOAD_TO_BYTE )
                    /*TODO: allign payload to byte for speed (!!! speed if header and postfix are byte alligned )*/
                    *payloadLenBits = BITS_TO_BYTES_CEIL(*payloadLenBits)*8;
      #endif
      if( *payloadLenBits > m_maxPacketSize){
          DEBUG << "!!!! Packet Size > maxPacketSize for packetId[" << packId << "].";
          *payloadLenBits = 0;
          ret = SOME_ERROR;
      }
  }
  else{
      DEBUG << "Invalid Input parameters";
      ret = WRONG_PARAMS;
  }
  return ret;
}
