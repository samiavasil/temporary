#ifndef _QPACKETCOLLECTOR_H
#define _QPACKETCOLLECTOR_H


#include <QObject>

#include "base/CPacketCollector.h"
#include <QMutex>

#include <QList>

#include <QByteArray>


class QPortIO;
class QProtocolPackFactory;

class QPacketCollector : public QObject, public CPacketCollector {
Q_OBJECT

  protected:
    QList<CPacket *> m_PacketsList;


  public:
    explicit QPacketCollector( QPortIO* port, QProtocolPackFactory* protocol, QObject* parent = 0 );

    virtual ~QPacketCollector();

    virtual int getRecPacket();

    virtual int transmitPacket(CPacket * packet);

    virtual int getRecPacketNum();

signals:
    int packetReceivedSignal();

public slots:
    void receivedBytesSlot();


  protected:
    virtual int appendReceivedBytes(const u8 * data, const int64 len);

    int collectPacket(CPacket * packet);

    virtual int getNumberOfReceivedBytes();

    virtual void lockData();

    virtual void unlockData();

    virtual const u8* getReceivedBytes();

    virtual void removeReceivedBytes(int byteNum);


  private:
    QByteArray m_Data;


  protected:
    QMutex m_Mutex;

};
#endif
