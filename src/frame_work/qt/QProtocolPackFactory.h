#ifndef _QPROTOCOLPACKFACTORY_H
#define _QPROTOCOLPACKFACTORY_H


#include "base/CProtocolPackFactory.h"
#include <QList>

#include <QMap>


class QProtocolLoader;

class QProtocolPackFactory : public CProtocolPackFactory {
  protected:
  typedef struct{
      msg_id_t  msgID;
      int bitLen;
  } msg_desc_t; 


  public:
    QProtocolPackFactory(QProtocolLoader * pLoader);


  protected:
    QMap< pack_id_t, QList<msg_id_t> > m_packMap;

    QMap< msg_id_t , msg_desc_t > m_msgMap;


  public:
    virtual void clearProtDefinitions();

    virtual int addPacket(const pack_id_t id);

    virtual int addMessage(const msg_id_t id, int len);

    virtual int addMessageToPacket(const pack_id_t packID, const msg_id_t msgID);

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen);

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset);

    virtual int getPacketLenFromData(const u8 * data);

    virtual pack_id_t getPacketTypeFromData(const u8 * data);

    virtual int getMessage(msg_id_t id, const u8 * data);

    virtual int setMessage(const msg_id_t msgId, const u8 * data);


  protected:
    virtual int checkPacketConsistency(const u8 * data);


  public:
    virtual int findPacketStart();


  protected:
    virtual int packetLen(const pack_id_t packId);

    virtual int getPacketMessagesNumber(const pack_id_t & packId);

    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num);

};
#endif
