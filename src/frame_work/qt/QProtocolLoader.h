#ifndef _QPROTOCOLLOADER_H
#define _QPROTOCOLLOADER_H


#include "base/global.h"

enum{
#define GEN_MSG_ENUMS
#include"ProtoGen.h"

};


enum{
#define GEN_PKT_ENUMS
#include"ProtoGen.h"

};

class FRAME_WORKSHARED_EXPORT QProtocolLoader {
protected:
    virtual int readProtocolData();

    virtual int getMsgCount();

    virtual int getMsgId(int number);

    virtual int getMaxPacketSize();

    virtual int getPacketCount();

    virtual pack_id_t getPackId(int number);

    virtual int getMsgsCountForPack(const pack_id_t packID);

    virtual msg_id_t getMsgIdForPack(const pack_id_t packID, int idx);

    virtual const char* getMsgDescription(const msg_id_t id);

    virtual int getMsgIdLen(const msg_id_t id, int * len);

    virtual int getHeaderLenBits();

    virtual int getPostFixLenBits();

    friend class  QProtocolDb;
};
#endif
