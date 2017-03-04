
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolDb.h"
#include "base/QPacket.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

//#define TEST_SPEED
#if defined(TEST_SPEED)
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#define TEST_NUM 10000000
void test_bit_set_time(CProtocolDb* m_pDB)
{



  time_t now;
  time_t end_time;
  double seconds;
  u8 data[2];

  time(&now);  /* get current time; same as: now = time(NULL)  */
  for( long long int i=0; i< TEST_NUM; i++ )
  {

      data[0]=0x12+i;
      data[1]=0x34;
      m_pDB->setMessage(AIN1_ENBLE,data);
      data[0]=0x56;
      data[1]=0x78+i;
      m_pDB->setMessage(AIN2_ENBLE,data);
      data[0]=0x9a+i;
      data[1]=0xbc;
      m_pDB->setMessage(AIN1_GAIN,data);
      data[0] = 0xde + i;
      data[1]=0x1f;
      m_pDB->setMessage(AIN2_GAIN,data);
  }

  time(&end_time);
  seconds = difftime( end_time, now );
  fprintf(stderr,"Test Set: Number = %d, Sec = %f  Num/Sec=%f\n",TEST_NUM,seconds, seconds? ((double)TEST_NUM)/seconds:-1 );
}
#endif

QProtocolPackFactory::QProtocolPackFactory(QProtocolDb *protDb, QObject * parent  ):QObject(parent) {
      DEBUG << "Create QProtocolPackFactory";
      m_pDB = NULL;
      if( NO_ERR != attachProtocolDb( protDb ) ){
          CRITICAL << "!!!Default ProtocolDB can't be attached to ProtocolPackFactory: Use attachProtocol()";
      }
      /*   if( NO_ERR == attachProtocolDb( new QProtocolDb() ) ){
         Attach default protocol loader - if you want you can change it with attachProtocol()
          if(  NO_ERR != attachProtocol( new QProtocolLoader() ) ) {
              CRITICAL << "!!!Default ProtocolLoader can't be attached to ProtocolPackFactory: Use attachProtocol()";
          }
      }
      else{

          CRITICAL << "!!!Default ProtocolDB can't be attached to ProtocolPackFactory: Use attachProtocol()";
      }*/
      ///TODO: DELLL ME -  This is for test only
#if defined(TEST_SPEED)
  test_bit_set_time( m_pDB);
#endif



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
    if( m_pDB ){
        delete m_pDB;
    }
}

int QProtocolPackFactory::attachProtocolDb(QProtocolDb *pDB ) {
    int ret = WRONG_PARAMS;
    if( pDB ){
        if( m_pDB ){
            delete m_pDB;
        }
        m_pDB  = pDB;
        ret = NO_ERR;
    }
    return ret;
}

QPacket* QProtocolPackFactory::createPacket(const pack_id_t packId) {
    QPacket * packet = NULL;

    if( PKT_ID_INVALID < packId ){
        return packet;
    }
    int payloadLenBits=0;
    if( NO_ERR == m_pDB->packetPayloadBitLen(packId, &payloadLenBits )){
        packet = new QPacket( packId,payloadLenBits + m_pDB->getProtocolHeaderLenBits() + m_pDB->getProtocolPostFixLenBits() );
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

QPacket* QProtocolPackFactory::createPacketFromData(const u8 * data) {
    QPacket * packet = NULL;
    if( NULL == data ){
        return packet;
    }

    packet = new QPacket( getPacketTypeFromData(data), getPacketLenFromData(data) );
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

int QProtocolPackFactory::setPacketMessage(QPacket * packet, msg_id_t msgId, const u8 * data) {
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

int QProtocolPackFactory::getPacketMessage(QPacket * packet, msg_id_t msgId, u8 * retData) {
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

int QProtocolPackFactory::getPacketHeader(QPacket * packet, u8 * header) {
  if( ( NULL == packet )||( NULL == header ) ){
      return WRONG_PARAMS;
  }
  return packet->getBits( 0, m_pDB->getProtocolHeaderLenBits(), header );
}

int QProtocolPackFactory::getPacketPostFix(QPacket * packet, u8 * retPostFix) {
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

int bitcmp( u8* src,u8* dest, int bit_num ){
    int num_bytes        = bit_num/8;
    int num_in_last_byte = bit_num%8;
    if( src && dest )
    {
        int i=0;
        for( i=0; i< num_bytes; i++ )
        {
            if( src[i] != dest[i] )
            {
                return 1;
            }
        }
        if( num_in_last_byte )
        {
            u8 mask = BIT_MASK_BEFORE_BIT_U8(num_in_last_byte);
            if( (src[i]&mask) != (dest[i]&mask) )
            {
                return 1;
            }
        }
    }
    return 0;
}

int QProtocolPackFactory::checkPacketConsistency(QPacket * packet) {
  int ret = WRONG_PARAMS;
  u32 postfixSize = BITS_TO_BYTES_CEIL(m_pDB->getProtocolPostFixLenBits());
  u8 postfix[ postfixSize ];
  u8 packPostfix[ postfixSize ];
  if( packet ){
      //TODO - postfix should be fixed (it can be not only simple CRC )
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_pDB->getProtocolPostFixLenBits() );
      ret = getPacketPostFix( packet,packPostfix );
      if( ( NO_ERR == ret ) && bitcmp( postfix, packPostfix, m_pDB->getProtocolPostFixLenBits() ) ){
         ret = WRONG_DATA;
      }
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

int QProtocolPackFactory::getMaxPacketLen() const{
    return m_pDB->getMaxPacketLen();
}

int QProtocolPackFactory::getProtocolHeaderLenBits() const{
    return m_pDB->getProtocolHeaderLenBits();
}

QProtocolDb *QProtocolPackFactory::getProtocolDb(){
    return m_pDB;
}

int QProtocolPackFactory::getPacketLenFromData(const u8 * data) {
    /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/
  return (((int)data[2])<<8)|((int)data[3]);                                                             
}

pack_id_t QProtocolPackFactory::getPacketTypeFromData(const u8 * data) {
   /*TODO - in curent moment header is hard coded should be maded to be loadable with ProtocolLoader*/  
   return (pack_id_t)(((int)data[0])<<8)|((int)data[1]);                                                
}

int QProtocolPackFactory::addPacketHeader(QPacket * packet) {
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

int QProtocolPackFactory::addPacketPostFix(QPacket * packet) {
  int ret = WRONG_PARAMS;
  if( packet ){
      u8 postfix[BITS_TO_BYTES_CEIL(m_pDB->getProtocolPostFixLenBits())];
      postfix[0]=calCulateCrc8( packet->data(), packet->packLenBits() - m_pDB->getProtocolPostFixLenBits() );
      ret = packet->setBits( BITS_TO_BYTES_CEIL(packet->packLenBits() - m_pDB->getProtocolPostFixLenBits())*8,m_pDB->getProtocolPostFixLenBits(),postfix );
  }
  return  ret;
}

int QProtocolPackFactory::calCulateCrc8(const u8 * data, int numBits) {
  int bytesNum = numBits/8;
  int bitsNum  = numBits%8;
  int i;
  u8 crc = 0;
  for( i=0; i< bytesNum;i++ ){
      crc ^= data[i];
  }
  if( bitsNum ){
      crc ^=  (data[i]&((1<<bitsNum)-1));
  }
  // ios:hex( crc );
  DEBUG << "CRC=" << std::hex << crc;
  return crc;
}

