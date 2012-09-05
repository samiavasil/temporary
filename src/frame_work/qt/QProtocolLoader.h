#ifndef _QPROTOCOLLOADER_H
#define _QPROTOCOLLOADER_H


#include "base/CProtocolLoader.h"

class QProtocolLoader : public CProtocolLoader {
  public:
    virtual int readProtocolData();

    virtual int getMsgCount();

    virtual int getMsgId(int number);

    virtual int getMaxPacketSize();

    virtual int getPacketCount();

    virtual pack_id_t getPackId(int number);

    virtual int getMsgsCountForPack(const pack_id_t packID);

    virtual msg_id_t getMsgIdForPack(const pack_id_t packID, int idx);


  protected:
    virtual int getMsgIdLen(const msg_id_t id, int *len);

    virtual int getHeaderSize();

    virtual int getPostFixSize();

};
#endif
