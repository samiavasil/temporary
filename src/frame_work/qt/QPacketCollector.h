#ifndef _QPACKETCOLLECTOR_H
#define _QPACKETCOLLECTOR_H


#include "base/global.h"
#include <QObject>

#include <QMutex>

#include <QList>

#include <QByteArray>


class CPortIO;
class CPacket;
class CProtocolPackFactory;

class FRAME_WORKSHARED_EXPORT QPacketCollector : public QObject {
    Q_OBJECT

protected:
    QList<CPacket *> m_PacketsList;


public:
    QPacketCollector(CPortIO * port, CProtocolPackFactory * protocol, QObject * parent = 0);

    virtual ~QPacketCollector();

    virtual int getRecPacket();

    virtual int transmitPacket(CPacket * packet);

    virtual int getRecPacketNum();

    bool isChained();

    int setProtocolFactory(CProtocolPackFactory *protocol);

    int setPort(CPortIO *port);

    int receiveBytes();

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
    typedef enum {
        COL_IDLE,
        COL_WAIT_FOR_HEADER,
        COL_WAIT_FOR_PACK
    } rec_states_t;

    typedef enum {
        TBD
    } trans_states_t;

    QMutex m_Mutex;

    CPortIO* m_PortIo;

    CProtocolPackFactory* m_Protocol;

    rec_states_t m_RecState;

    trans_states_t m_TransState;

};
#endif
