#ifndef _QPACKETCOLLECTOR_H
#define _QPACKETCOLLECTOR_H


#include <QObject>

#include "base/CPacketCollector.h"
#include <QByteArray>

#include <QList>


class CFrameWork;
class CPacket;

class QPacketCollector : public QObject, public CPacketCollector {
Q_OBJECT

  public:
    QPacketCollector(CFrameWork * cFwk);

    ~QPacketCollector();

    virtual int getRecPacket();

    virtual int getRecPacketNum();

signals:
    int packetReceivedSignal();

public slots:
    void receivedBytesSlot();


  protected:
    virtual int appendReceivedBytes(const u8 * data, const int64 len);

    int collectPacket(CPacket * packet);

    virtual int getNumberOfReceivedBytes();

    virtual const u8* getReceivedBytes();

    virtual void removeReceivedBytes(int byteNum);


  private:
    QByteArray m_Data;


  protected:
    QList<CPacket *> m_PacketsList;

};
#endif
