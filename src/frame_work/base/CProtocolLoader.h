#ifndef _CPROTOCOLLOADER_H
#define _CPROTOCOLLOADER_H


#include "global.h"
#include "base/CProtocolPackFactory.h"

class CProtocolLoader {
  public:
    virtual int loadProtocolDefinition(CProtocolPackFactory * protoFactory);

    virtual int readProtocolData() = 0;

    virtual int getMsgCount() = 0;

    virtual int getMsgId(int number) = 0;

    virtual int getMaxPacketSize() = 0;

    virtual int getPacketCount() = 0;

    virtual pack_id_t getPackId(int number) = 0;

    virtual int getMsgsCountForPack(const pack_id_t & packID) = 0;

    virtual msg_id_t getMsgIdForPack(const pack_id_t & packID, int idx) = 0;

};
#endif
