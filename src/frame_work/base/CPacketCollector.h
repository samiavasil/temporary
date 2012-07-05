#ifndef _CPACKETCOLLECTOR_H
#define _CPACKETCOLLECTOR_H


class CPacket;
class CProtocolPackFactory;
class CPortIO;
class CFrameWork;

class CPacketCollector {
  private:
    CFrameWork * m_fWork;


  public:
    virtual int getRecPacket() = 0;

    virtual int getRecPacketNum() = 0;

    virtual int packetReceivedSignal() = 0;

    virtual int receivedBytesSlot() = 0;

};
#endif
