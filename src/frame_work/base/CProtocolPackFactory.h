#ifndef _CPROTOCOLPACKFACTORY_H
#define _CPROTOCOLPACKFACTORY_H


class CProtocolLoader;
class CPacket;

class CProtocolPackFactory {
  public:
    CProtocolPackFactory();


  protected:
    int clearMsgDefinitions();

    int clearProtDeinfitions();


  public:
    int addPacket();

    int addMessage();

    int addMessageToPacket();

    int addPacketHeader();

    int addPacketPostFix();

    int createPacket();

    int createPacketFromData();

    int findPacketStart();

    int getMaxPacketSize();

    int getPacketLen();

    int getPacketType();

    int getProtocolHeaderSize();

    int setProtocolHeaderSize();

    int getProtocolPostFixLen();

    int setProtolPostFixLen();

    int setMaxPacketSize();

    int setMessage();

};
#endif
