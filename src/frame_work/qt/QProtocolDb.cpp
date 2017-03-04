#include "QProtocolDb.h"
#include"qt/QProtocolLoader.h"
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

int QProtocolDb::getProtocolHeaderLenBits() const {
    return m_hDrLenBits;
}

void QProtocolDb::setProtocolHeaderLenBits(int lenBits) {
    m_hDrLenBits = lenBits;
}

int QProtocolDb::getProtocolPostFixLenBits() const {
    return m_postFixLenBits;
}

void QProtocolDb::setProtocolPostFixLenBits(int lenBits) {
    m_postFixLenBits = lenBits;
}

int QProtocolDb::getMaxPacketLen() {
    return m_maxPacketSize;
}

void QProtocolDb::setMaxPacketLen(int max_size) {
    m_maxPacketSize = max_size;
}

int QProtocolDb::loadProtocolDefinition(QProtocolLoader & protLd ) {
    int errCode = SOME_ERROR;
    int MsgCount  = 0;
    int PackCount = 0;
    pack_id_t packID;
    msg_id_t  msgID;
    int msgLen;
    int i,j;
    clearProtDefinitions();
    errCode = protLd.readProtocolData();
    if( NO_ERR  == errCode ){

        int max_pack_size = protLd.getMaxPacketSize( );
        if( 0 < max_pack_size ){
            setMaxPacketLen( max_pack_size );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet size";
            return errCode;
        }
        int lenBits = protLd.getHeaderLenBits();
        if( 0 < lenBits ){
            setProtocolHeaderLenBits( lenBits );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet header size";
            return errCode;
        }
        lenBits = protLd.getPostFixLenBits();
        if( 0 <= lenBits ){
            setProtocolPostFixLenBits( lenBits );
        }
        else{
            errCode = WRONG_DATA;
            CRITICAL << "Error[" << errCode << "]: Can't read packet post fix size";
            return errCode;
        }
        MsgCount = protLd.getMsgCount();
        for( i=0; i < MsgCount;i++ ){
            msgID  = protLd.getMsgId(i);
            if(  MSG_ID_INVALID != msgID ){
                errCode = protLd.getMsgIdLen(msgID,&msgLen);
                if( NO_ERR == errCode ){
                    errCode =  addMessage( msgID, msgLen );
                    if( NO_ERR != errCode ){
                        CRITICAL << "Error[" << errCode << "]:Can't add message ID[" << msgID << "]";
                        return errCode;
                    }
                }
                else{
                    CRITICAL << "Error[" << errCode << "]:Can't get Len for message ID[" << msgID << "]";
                    return errCode;
                }
            }
            else{
                /*TODO Someting*/
                errCode = WRONG_DATA;
                CRITICAL << "TODO: " << __func__ << " : MSG_ID_INVALID";
                return errCode;
            }
        }
        PackCount = protLd.getPacketCount();

        for( i=0; i < PackCount;i++ ){
            packID = protLd.getPackId(i);
            if( PKT_ID_INVALID != packID ){
                errCode =  addPacket( packID );
                if( NO_ERR != errCode ){
                    CRITICAL << "Error[" << errCode << "]:Can't add packet ID[" << packID << "]";
                    return errCode;
                }

                MsgCount = protLd.getMsgsCountForPack( packID );
                if( ( 0 < MsgCount )&&( max_pack_size > MsgCount ) ){
                    for( j = 0; j < MsgCount; j++ ){
                        msgID = protLd.getMsgIdForPack( packID, j );
                        if( MSG_ID_INVALID != msgID ){
                            errCode =  addMessageToPacket( packID, msgID );
                            if( NO_ERR != errCode ){
                                CRITICAL << "Error[" << errCode << "]:Invalid Message ID[" << msgID << "]";
                                return errCode;
                            }
                        }
                        else{
                            CRITICAL <<  "Error[" << errCode << "]:Invalid Message ID["<< msgID
                                      <<  "] for pack ID[" << packID << "]";
                        }
                    }
                }
                else{
                    /*TODO Someting*/
                    if( 0 >= MsgCount ){
                        CRITICAL << "TODO: " << __func__ << " : Packet without messages";
                    }
                    else{
                        CRITICAL << "TODO: " << __func__ << " : Max messages in packet limit is exceeded";
                    }
                }
            }
        }
    }

    return errCode;
}

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
