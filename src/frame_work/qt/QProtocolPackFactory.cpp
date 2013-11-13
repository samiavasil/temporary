
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include "base/CPacket.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QProtocolPackFactory::QProtocolPackFactory(QProtocolLoader * pLoader, QObject * parent):CProtocolPackFactory(pLoader),QObject(parent) {
      DEBUG << "Create QProtocolPackFactory";
      if(  attachProtocolLoader(pLoader) ) {
          DEBUG << "!!!ProtocolLoader isn't attached to ProtocolPackFactory: Use attachProtocolLoader()";
      }
      //4231 4 7 11 6
      u8 data[2];
      data[0]=0xff;
      data[1]=0xff;
      setMessage(AIN1_ENBLE,data);
      data[0]=0xff;
      data[1]=0xff;
      setMessage(AIN1_ENBLE,data);
      data[0]=0xff;
      data[1]=0xff;
      setMessage(AIN2_ENBLE,data);
      data[0]=0xff;
      data[1]=0xff;
      setMessage(AIN1_ENBLE,data);
  
#ifdef DUMP_PROTOCOL_LOAD
      DEBUG << "DUMP protocol loaded packet types");
      QMapIterator< pack_id_t, QList<msg_id_t> > i(m_packMap);
      while (i.hasNext()) {
          i.next();
          DEBUG <<  "PACKET ID[%d] MESSAGES:",i.key() );
          QList<msg_id_t> m_Id = i.value();
          for(int j=0;j < m_Id.size() ;j++){
              DEBUG <<  "       MSG ID[%d] size=%d,",m_Id.value(j), m_msgMap.value(m_Id.value(j)).bitLen );
              /*for(int i=0;i < BITS_TO_BYTES_CEIL(m_msgMap.value(m_Id.value(j)).bitLen);i++){
                    fprintf(stderr," %02x",m_msgMap.value(m_Id.value(j)).data[i]);
                }
                fprintf(stderr,"\n\n");*/
          }
  
      }
#endif
}

QProtocolPackFactory::~QProtocolPackFactory() {
  clearProtDefinitions();
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
          DEBUG << "Packet Id["<< id <<"] already exist.";
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
          DEBUG << "Message Id["<< id << "] already exist.";
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

int QProtocolPackFactory::getMessage(msg_id_t id, const u8 ** data) {
      int ret = NO_ERR;
      if( ( 0 != data ) && ( true == m_msgMap.contains( id ) ) ){
          *data = m_msgMap[id].data;
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

int QProtocolPackFactory::getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) {
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

int QProtocolPackFactory::getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) {
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

int QProtocolPackFactory::packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits) {
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
  		//#define ALLIGN_PAYLOAD_TO_BYTE
#if  defined( ALLIGN_PAYLOAD_TO_BYTE )
              /*TODO: allign payload to byte for speed (!!! speed if header and postfix are byte alligned )*/
              *payloadLenBits = BITS_TO_BYTES_CEIL(*payloadLenBits)*8;
#endif
  
          }
          else{
              *payloadLenBits = 0;
              DEBUG << "Wrong Message Id[" << msgId <<"] for packetId[" << packId << "]";
              ret = SOME_ERROR;
              break;
          }
      }
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

int QProtocolPackFactory::checkPacketConsistency(CPacket * packet) {
  int ret = WRONG_PARAMS;
  u8 postfix[BITS_TO_BYTES_CEIL(m_postFixLenBits)];//todo sometig wrong here...not checked
  u8 packPostfix[BITS_TO_BYTES_CEIL(m_postFixLenBits)];
  if( packet ){
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_postFixLenBits );
      ret = getPacketPostFix( packet,packPostfix );
  }
  return ret;
}

int QProtocolPackFactory::findPacketStart(const u8 * data, int len) {
  int offset = -1;                                                                                          
  int hdrSizeBytes = BITS_TO_BYTES_CEIL( m_hDrLenBits );                                                    
  /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/       
  for( int i=0;i <= ( len - hdrSizeBytes );i++ ){                                                           
      pack_id_t packId = (((int)data[i])<<8)|((int)data[i+1]);                                              
      if( m_packMap.contains(packId) ){                                                                     
          offset = i;                                                                                       
          break;                                                                                            
      }                                                                                                     
  }                                                                                                         
  return offset;                                                                                            
}

int QProtocolPackFactory::getPacketLenFromData(const u8 * data) {
  /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/    
  return (((int)data[2])<<8)|((int)data[3]);                                                             
}

pack_id_t QProtocolPackFactory::getPacketTypeFromData(const u8 * data) {
   /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/  
   return (pack_id_t)(((int)data[0])<<8)|((int)data[1]);                                                
}

int QProtocolPackFactory::addPacketHeader(CPacket * packet) {
  /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/
  int ret = WRONG_PARAMS;
  if( packet&&( PKT_ID_INVALID != packet->packType() ) ){
      pack_id_t type = packet->packType();
      u8 hdr[BITS_TO_BYTES_CEIL(m_hDrLenBits)];
      int len = packet->packLenBits();
      hdr[0]=(type>>8)&0xff;
      hdr[1]=type&0xff;
      hdr[2]=(len>>8)&0xff;
      hdr[3]=len&0xff;
      ret = packet->setBits(0,m_hDrLenBits,hdr);
  }
  return ret;
}

int QProtocolPackFactory::addPacketPostFix(CPacket * packet) {
  int ret = WRONG_PARAMS;
  if( packet ){
      u8 postfix[BITS_TO_BYTES_CEIL(m_postFixLenBits)];
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_postFixLenBits );
      ret = packet->setBits( packet->packLenBits() - m_postFixLenBits,m_postFixLenBits,postfix );
  }
  return  ret;
}

int QProtocolPackFactory::calCulateCrc8(const u8 * data, int numBits) {
  int bytesNum = numBits/8;
  int bitsNum  = numBits%8;
  int i;
  u8 crc = 0;
  for( i=0; i< bytesNum;i++ ){
      crc |= data[i];
  }
  if( bitsNum ){
      crc |=  (data[i]&((1<<bitsNum)-1));
  }
  // ios:hex( crc );
  DEBUG << "CRC=" << std::hex << crc;
  return crc;
}

