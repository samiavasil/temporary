#ifndef QPROTOCOLDB_H
#define QPROTOCOLDB_H
#include"base/CProtocolDb.h"
#include"base/CProtocolLoader.h"
#include <QList>
#include <QMap>
#include <QObject>

//TODO FIX ME: remove from other mesta
#define  PACK_ID_TYPE_BIT_SIZE  (sizeof(pack_id_t)*8)
#define  MSG_ID_TYPE_BIT_SIZE    (sizeof(msg_id_t)*8)
#define  PKT_ID_INVALID     ((pack_id_t)(  (  (1<<(PACK_ID_TYPE_BIT_SIZE-1) ) -  ((unsigned int) 1) )|(PACK_ID_TYPE_BIT_SIZE-1) ))
#define  MSG_ID_INVALID     ((msg_id_t)(  (  (1<<(MSG_ID_TYPE_BIT_SIZE-1) )  - ((unsigned int) 1)  )|(MSG_ID_TYPE_BIT_SIZE-1)   ))


class FRAME_WORKSHARED_EXPORT QProtocolDb : public CProtocolDb
{
public:
    virtual int addPacket(const pack_id_t id);

    virtual int isTherePacketId(const pack_id_t id);

    virtual int addMessage(const msg_id_t id, int len);

    virtual int getMessage(msg_id_t id, const u8 ** data);

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen);

    virtual int getPacketMessagesNumber(const pack_id_t packId, int * msgNum);

    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num);

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset);

    virtual int addMessageToPacket(const pack_id_t packID, const msg_id_t msgID);

    virtual int packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits);

    virtual int setMessage(const msg_id_t msgId, const u8 * data);
protected:
    virtual void clearProtDefinitions();
protected:
typedef struct{
    msg_id_t  msgID;
    int bitLen;
    u8*     data;
} msg_desc_t;

protected:

    QMap< pack_id_t, QList<msg_id_t> > m_packMap;

    QMap< msg_id_t , msg_desc_t > m_msgMap;
};

#endif // QPROTOCOLDB_H
