#ifndef _CPACKETCOLLECTOR_H
#define _CPACKETCOLLECTOR_H


#include "global.h"
class CPacket;
class CProtocolPackFactory;
class CPortIO;
class CFrameWork;

class CPacketCollector {

  public:
    explicit CPacketCollector( CPortIO* port, CProtocolPackFactory* protocol );

    virtual ~CPacketCollector();

    virtual int getRecPacket() = 0;

    virtual int packetReceivedSignal() = 0;

    virtual int getRecPacketNum() = 0;

    virtual int receiveBytes();

    bool        isChained();

  protected:
    virtual int appendReceivedBytes(const u8 * data, const int64 len) = 0;

    virtual int collectPacket(CPacket * packet) = 0;

    virtual int getNumberOfReceivedBytes() = 0;

    virtual void lockData() = 0;

    virtual void unlockData() = 0;

    virtual const u8* getReceivedBytes() = 0;

    virtual void removeReceivedBytes(int byteNum) = 0;


  public:
    virtual int transmitPacket(CPacket * packet) = 0;

protected:
typedef enum {
      COL_IDLE,
      COL_WAIT_FOR_HEADER,
      COL_WAIT_FOR_PACK
} rec_states_t;
protected:
typedef enum {
      TBD
} trans_states_t;

  protected:
    CPortIO *m_PortIo;
    CProtocolPackFactory * m_Protocol;
    rec_states_t m_RecState;
    trans_states_t m_TransState;

};
#endif
