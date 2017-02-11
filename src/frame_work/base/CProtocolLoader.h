#ifndef _CPROTOCOLLOADER_H
#define _CPROTOCOLLOADER_H


#include "global.h"
#include "base/CProtocolPackFactory.h"
class CProtocolDb;

class FRAME_WORKSHARED_EXPORT CProtocolLoader {
public:
     virtual ~CProtocolLoader(){}
protected:

    virtual int readProtocolData() = 0;

    virtual int getMsgCount() = 0;

    virtual int getMsgId(int number) = 0;

    virtual int getMaxPacketSize() = 0;

    virtual int getPacketCount() = 0;

    virtual pack_id_t getPackId(int number) = 0;

    virtual int getMsgsCountForPack(const pack_id_t packID) = 0;

    virtual const char*  getMsgDescription(const msg_id_t id) = 0;

    virtual int getMsgIdLen(const msg_id_t id, int * len) = 0;

    virtual msg_id_t getMsgIdForPack(const pack_id_t packID, int idx) = 0;

    virtual int getHeaderLenBits() = 0;

    virtual int getPostFixLenBits() = 0;

    friend class  CProtocolDb;

};
#endif

