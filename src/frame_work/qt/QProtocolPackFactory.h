#ifndef _QPROTOCOLPACKFACTORY_H
#define _QPROTOCOLPACKFACTORY_H


#include "base/CProtocolPackFactory.h"
#include <QList>

#include <QMap>


class QProtocolLoader;

class QProtocolPackFactory : public CProtocolPackFactory {
  public:
    QProtocolPackFactory(QProtocolLoader * pLoader);

    ~QProtocolPackFactory();

  protected:
  typedef struct{
      msg_id_t  msgID;
      int bitLen;
      u8*     data; 
  } msg_desc_t; 


  protected:
    QMap< pack_id_t, QList<msg_id_t> > m_packMap;

    QMap< msg_id_t , msg_desc_t > m_msgMap;


  public:
    virtual void clearProtDefinitions();

    virtual int addPacket(const pack_id_t id);

    virtual int addMessage(const msg_id_t id, int len);

    virtual int addMessageToPacket(const pack_id_t packID, const msg_id_t msgID);

    virtual int getMessage(msg_id_t id, const u8 * data);

    virtual int setMessage(const msg_id_t msgId, const u8 * data);

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen);

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset);


  protected:
    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num);

    virtual int getPacketMessagesNumber(const pack_id_t packId, int * msgNum);

    virtual int packetLen(const pack_id_t packId, int * packLenBits);

    virtual int checkPacketConsistency(const u8 * data);


  public:
    virtual int findPacketStart();

    virtual int getPacketLenFromData(const u8 * data);

    virtual pack_id_t getPacketTypeFromData(const u8 * data);

};
#endif
