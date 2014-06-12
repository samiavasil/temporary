#ifndef CPROTOCOLDB_H
#define CPROTOCOLDB_H

#include "global.h"

typedef int pack_id_t;
typedef int msg_id_t;

class CProtocolLoader;
class CProtocolDb
{
public:
    CProtocolDb();
    virtual ~CProtocolDb(){}
    int loadProtocolDefinition( CProtocolLoader *protLd );
    virtual void clearProtDefinitions() = 0;

    virtual int addPacket(const pack_id_t id) = 0;

    virtual int isTherePacketId(const pack_id_t id) = 0;

    virtual int addMessage(const msg_id_t id, int len) = 0;

    virtual int getMessage(msg_id_t id, const u8 ** data) = 0;

    virtual int getMessageBitLen(msg_id_t msgId, int * msgLen) = 0;

    virtual int getPacketMessagesNumber(const pack_id_t packId, int * msgNum) = 0;

    virtual int getPacketMessagesId(const pack_id_t packId, msg_id_t * msgArr, int num) = 0;

    virtual int getMessageBitOffsetInPack(pack_id_t packId, msg_id_t msgId, int * offset) = 0;

    virtual int addMessageToPacket(const pack_id_t packID, const msg_id_t msgID) = 0;

    virtual int packetPayloadBitLen(const pack_id_t packId, int * payloadLenBits) = 0;

    virtual int setMessage(const msg_id_t msgId, const u8 * data) = 0;

    void setProtocolHeaderLenBits(int lenBits);

    void setProtocolPostFixLenBits(int lenBits);

    int getProtocolPostFixLenBits() const;

    int  getProtocolHeaderLenBits() const;

    virtual void setMaxPacketLen(int max_size);

    int getMaxPacketLen();

protected:
    int m_hDrLenBits;

    int m_postFixLenBits;

    int m_maxPacketSize;
};

#endif // CPROTOCOLDB_H
