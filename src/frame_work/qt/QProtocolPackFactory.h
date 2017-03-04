#ifndef _QPROTOCOLPACKFACTORY_H
#define _QPROTOCOLPACKFACTORY_H


#include "base/global.h"
#include <QList>

#include <QMap>

#include <QObject>



class QPacket;
class QProtocolDb;

class FRAME_WORKSHARED_EXPORT QProtocolPackFactory : public QObject {
public:
    QProtocolPackFactory(  QProtocolDb* protDb  = NULL, QObject * parent = 0);

    virtual ~QProtocolPackFactory();

    virtual int getPacketLenFromData(const u8 * data);

    virtual int findPacketStart(const u8 * data, int len);
    virtual int getMaxPacketLen() const;
    int  getProtocolHeaderLenBits() const;
    QProtocolDb* getProtocolDb();

    int attachProtocolDb( QProtocolDb *pDB);
    QPacket *createPacket(const pack_id_t packId);
    QPacket *createPacketFromData(const u8 *data);
    virtual int addPacketHeader(QPacket * packet);
    virtual int addPacketPostFix(QPacket * packet);
protected:
    typedef struct{
        msg_id_t  msgID;
        int bitLen;
        u8*     data;
    } msg_desc_t;

protected:

    virtual pack_id_t getPacketTypeFromData(const u8 * data);

    virtual int checkPacketConsistency(QPacket * packet);

    int calCulateCrc8(const u8 * data, int numBits);
protected:
    QProtocolDb*      m_pDB;
    int setPacketMessage(QPacket *packet, msg_id_t msgId, const u8 *data);
    int getPacketMessage(QPacket *packet, msg_id_t msgId, u8 *retData);
    int getPacketHeader(QPacket *packet, u8 *header);
    int getPacketPostFix(QPacket *packet, u8 *retPostFix);
};
#endif
