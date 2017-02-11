#ifndef _CPROTOCOLPACKFACTORY_H
#define _CPROTOCOLPACKFACTORY_H


#include "global.h"
#include "base/CProtocolDb.h"

#define  PACK_ID_TYPE_BIT_SIZE  (sizeof(pack_id_t)*8)
#define  MSG_ID_TYPE_BIT_SIZE    (sizeof(msg_id_t)*8)
#define  PKT_ID_INVALID     ((pack_id_t)(  (  (1<<(PACK_ID_TYPE_BIT_SIZE-1) ) -  ((unsigned int) 1) )|(PACK_ID_TYPE_BIT_SIZE-1) ))
#define  MSG_ID_INVALID     ((msg_id_t)(  (  (1<<(MSG_ID_TYPE_BIT_SIZE-1) )  - ((unsigned int) 1)  )|(MSG_ID_TYPE_BIT_SIZE-1)   ))

class CPacket;


class FRAME_WORKSHARED_EXPORT CProtocolPackFactory {
  public:
    CProtocolPackFactory( CProtocolDb* protDb = NULL );

    virtual ~CProtocolPackFactory();

    int attachProtocolDb(  CProtocolDb * pDB );

    virtual int findPacketStart(const u8 * data, int len) = 0;

    virtual int getPacketLenFromData(const u8 * data) = 0;

    virtual CPacket* createPacket(const pack_id_t packId);

    virtual CPacket* createPacketFromData(const u8 * data);

    virtual int addPacketHeader(CPacket * packet) = 0;

    virtual int addPacketPostFix(CPacket * packet) = 0;

    virtual int getMaxPacketLen() const{
        return m_pDB->getMaxPacketLen();
    }
    int  getProtocolHeaderLenBits() const{
       return m_pDB->getProtocolHeaderLenBits();
    }
    CProtocolDb* getProtocolDb(){
        return m_pDB;
    }

  protected:

    virtual int checkPacketConsistency(CPacket * packet) = 0;

    virtual pack_id_t getPacketTypeFromData(const u8 * data) = 0;

    int setPacketMessage(CPacket * packet, msg_id_t msgId, const u8 * data);

    int getPacketMessage(CPacket * packet, msg_id_t msgId, u8 * retData);

    int getPacketPostFix(CPacket * packet, u8 * retPostFix);

    int getPacketHeader(CPacket * packet, u8 * header);

  protected:
    CProtocolDb*      m_pDB;
};

/*inline int CProtocolPackFactory::getProtocolHeaderLenBits() const {
  return m_hDrLenBits;
}

inline void CProtocolPackFactory::setProtocolHeaderLenBits(int lenBits) {
  m_hDrLenBits = lenBits;
}

inline int CProtocolPackFactory::getProtocolPostFixLenBits() const {
  return m_postFixLenBits;
}

inline void CProtocolPackFactory::setProtocolPostFixLenBits(int lenBits) {
  m_postFixLenBits = lenBits;
}*/

#endif
