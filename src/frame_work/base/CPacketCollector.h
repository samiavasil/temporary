#ifndef _CPACKETCOLLECTOR_H
#define _CPACKETCOLLECTOR_H


#include "global.h"
class CPacket;
class CProtocolPackFactory;
class CPortIO;
class CFrameWork;

class CPacketCollector {
  private:
    CFrameWork * m_fWork;


  public:
    CPacketCollector(CFrameWork * fWk);

    virtual int getRecPacket() = 0;

    virtual int packetReceivedSignal() = 0;

    virtual int getRecPacketNum() = 0;

    virtual int receiveBytes();


  protected:
    virtual int appendReceivedBytes(const u8 * data, const int64 len) = 0;

    virtual int collectPacket(CPacket * packet) = 0;

    virtual int getNumberOfReceivedBytes() = 0;

    virtual const u8* getReceivedBytes() = 0;

    virtual void removeReceivedBytes(int byteNum) = 0;

protected:
typedef enum {
      COL_IDLE,
      COL_WAIT_FOR_HEADER,
      COL_WAIT_FOR_PACK
} states_t ;
    states_t state;

};
#endif
