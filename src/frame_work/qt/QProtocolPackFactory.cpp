
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include "qt/QProtocolDb.h"
#include "base/CPacket.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QProtocolPackFactory::QProtocolPackFactory(QProtocolDb * pDB, QObject * parent):CProtocolPackFactory(pDB),QObject(parent) {
      DEBUG << "Create QProtocolPackFactory";
      if(  attachProtocolLoader( new QProtocolLoader() ) ) {
          DEBUG << "!!!ProtocolLoader isn't attached to ProtocolPackFactory: Use attachProtocolLoader()";
     //     m_pLoader = NULL;
      }
      else{
       //   m_pLoader = pLoader;
      }
      //4231 4 7 11 6
      ///TODO: DELLL ME -  This is for test only




      u8 data[2];
      data[0]=0xff;
      data[1]=0xff;
      m_pDB->setMessage(AIN1_ENBLE,data);
      data[0]=0xff;
      data[1]=0xff;
      m_pDB->setMessage(AIN2_ENBLE,data);
      data[0]=0xff;
      data[1]=0xff;
      m_pDB->setMessage(AIN1_GAIN,data);
      data[0]=0xff;
      data[1]=0xff;
      m_pDB->setMessage(AIN2_GAIN,data);


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
    /*if( m_pLoader )
      delete m_pLoader;*/
}


int QProtocolPackFactory::checkPacketConsistency(CPacket * packet) {
  int ret = WRONG_PARAMS;
  u8 postfix[BITS_TO_BYTES_CEIL(m_pDB->getProtocolPostFixLenBits())];//todo sometig wrong here...not checked
  u8 packPostfix[BITS_TO_BYTES_CEIL(m_pDB->getProtocolPostFixLenBits())];
  if( packet ){
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_pDB->getProtocolPostFixLenBits() );
      ret = getPacketPostFix( packet,packPostfix );
  }
  return ret;
}

int QProtocolPackFactory::findPacketStart(const u8 * data, int len) {
  int offset = -1;                                                                                          
  int hdrSizeBytes = BITS_TO_BYTES_CEIL( m_pDB->getProtocolHeaderLenBits() );
  /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/       
  for( int i=0;i <= ( len - hdrSizeBytes );i++ ){                                                           
      pack_id_t packId = (((int)data[i])<<8)|((int)data[i+1]);                                              
      if( m_pDB->isTherePacketId(packId) ){
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
      u8 hdr[BITS_TO_BYTES_CEIL(m_pDB->getProtocolHeaderLenBits())];
      int len = packet->packLenBits();
      hdr[0]=(type>>8)&0xff;
      hdr[1]=type&0xff;
      hdr[2]=(len>>8)&0xff;
      hdr[3]=len&0xff;
      ret = packet->setBits(0,m_pDB->getProtocolHeaderLenBits(),hdr);
  }
  return ret;
}

int QProtocolPackFactory::addPacketPostFix(CPacket * packet) {
  int ret = WRONG_PARAMS;
  if( packet ){
      u8 postfix[BITS_TO_BYTES_CEIL(m_pDB->getProtocolPostFixLenBits())];
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_pDB->getProtocolPostFixLenBits() );
      ret = packet->setBits( packet->packLenBits() - m_pDB->getProtocolPostFixLenBits(),m_pDB->getProtocolPostFixLenBits(),postfix );
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

