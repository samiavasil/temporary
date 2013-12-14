#ifndef _QPROTOCOLPACKFACTORY_H
#define _QPROTOCOLPACKFACTORY_H


#include "frame_work_global.h"
#include "base/CProtocolPackFactory.h"
#include <QList>

#include <QMap>

#include <QObject>


class QProtocolLoader;
class CPacket;

class FRAME_WORKSHARED_EXPORT QProtocolPackFactory : public CProtocolPackFactory, public QObject {
  public:
    QProtocolPackFactory(QProtocolLoader * pLoader, QObject * parent = 0);

    virtual ~QProtocolPackFactory();

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

    virtual int getMessage(msg_id_t id, const u8 ** data);

    virtual int setMessage(const msg_id_t msgId, const u8 * data);

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen);

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset);


  protected:
    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num);

    virtual int getPacketMessagesNumber(const pack_id_t packId, int * msgNum);

    virtual int packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits);

    virtual int checkPacketConsistency(CPacket * packet);


  public:
    virtual int findPacketStart(const u8 * data, int len);

    virtual int getPacketLenFromData(const u8 * data);

    virtual pack_id_t getPacketTypeFromData(const u8 * data);


  protected:
    virtual int addPacketHeader(CPacket * packet);

    virtual int addPacketPostFix(CPacket * packet);

    int calCulateCrc8(const u8 * data, int numBits);

};
#endif
