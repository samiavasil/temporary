#ifndef _CPROTOCOLPACKFACTORY_H
#define _CPROTOCOLPACKFACTORY_H


#include "global.h"
typedef int pack_id_t;
typedef int msg_id_t;

#define  PACK_ID_TYPE_BIT_SIZE  (sizeof(pack_id_t)*8)
#define  MSG_ID_TYPE_BIT_SIZE    (sizeof(msg_id_t)*8)
#define  PKT_ID_INVALID     ((pack_id_t)(  (  (1<<(PACK_ID_TYPE_BIT_SIZE-1) ) -  ((unsigned int) 1) )|(PACK_ID_TYPE_BIT_SIZE-1) ))
#define  MSG_ID_INVALID     ((msg_id_t)(  (  (1<<(MSG_ID_TYPE_BIT_SIZE-1) )  - ((unsigned int) 1)  )|(MSG_ID_TYPE_BIT_SIZE-1)   ))

class CProtocolLoader;
class CPacket;

class CProtocolPackFactory {
  public:
    CProtocolPackFactory(CProtocolLoader * pLoader);

     int attachProtocolLoader(CProtocolLoader * pLoader);


  protected:
    virtual int checkPacketConsistency(CPacket * packet) = 0;


  public:
    virtual void clearProtDefinitions() = 0;

    virtual int addPacket(const pack_id_t id) = 0;

    virtual int addMessage(const msg_id_t id, int len) = 0;

    virtual int addMessageToPacket(const pack_id_t packID, const msg_id_t msgID) = 0;

    virtual int findPacketStart(const u8 * data, int len) = 0;

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen) = 0;

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) = 0;

    virtual int getPacketLenFromData(const u8 * data) = 0;

    virtual pack_id_t getPacketTypeFromData(const u8 * data) = 0;

    virtual int getMessage(msg_id_t id, const u8 ** data) = 0;

    virtual int setMessage(const msg_id_t msgId, const u8 * data) = 0;

    virtual CPacket* createPacket(const pack_id_t packId);

    virtual CPacket* createPacketFromData(const u8 * data);


  protected:
    int setPacketMessage(CPacket * packet, msg_id_t msgId, const u8 * data);

    int getPacketMessage(CPacket * packet, msg_id_t msgId, u8 * retData);


  public:
    virtual int getMaxPacketLen();

    virtual void setMaxPacketLen(int max_size);


  protected:
    int getPacketHeader(CPacket * packet, u8 * header);


  public:
    virtual int addPacketHeader(CPacket * packet) = 0;

    virtual int addPacketPostFix(CPacket * packet) = 0;


  protected:
    int getPacketPostFix(CPacket * packet, u8 * retPostFix);

    virtual int packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits) = 0;

    virtual int getPacketMessagesNumber(const pack_id_t packId, int * msgNum) = 0;

    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) = 0;


  public:
    inline int getProtocolHeaderLenBits() const;

    inline void setProtocolHeaderLenBits(int lenBits);

    inline int getProtocolPostFixLenBits() const;

    inline void setProtocolPostFixLenBits(int lenBits);


  protected:
    int m_hDrLenBits;

    int m_postFixLenBits;

    int m_maxPacketSize;

};
inline int CProtocolPackFactory::getProtocolHeaderLenBits() const {
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
}

#endif
