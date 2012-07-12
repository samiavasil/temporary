#ifndef _CPACKET_H
#define _CPACKET_H


#include "global.h"
class CPacket {
  public:
    CPacket();

    ~CPacket();

    virtual int setMsg();

    virtual int setData();

    virtual int setHeader();

    virtual int setPostFix();

    virtual int pack();

    virtual int data();

    virtual int dataLen();

    virtual int packType();

};
#endif
