#ifndef _QPROTOCOLPACKFACTORY_H
#define _QPROTOCOLPACKFACTORY_H


#include "frame_work_global.h"
#include "base/CProtocolPackFactory.h"
#include <QList>

#include <QMap>

#include <QObject>



class CPacket;
class CProtocolDb;

class FRAME_WORKSHARED_EXPORT QProtocolPackFactory : public CProtocolPackFactory, public QObject {
  public:
    QProtocolPackFactory(  CProtocolDb* protDb , QObject * parent = 0);

    virtual ~QProtocolPackFactory();

    virtual int getPacketLenFromData(const u8 * data);

    virtual int findPacketStart(const u8 * data, int len);

  protected:
  typedef struct{
      msg_id_t  msgID;
      int bitLen;
      u8*     data; 
  } msg_desc_t; 

  protected:

    virtual pack_id_t getPacketTypeFromData(const u8 * data);

    virtual int checkPacketConsistency(CPacket * packet);

    virtual int addPacketHeader(CPacket * packet);

    virtual int addPacketPostFix(CPacket * packet);

    int calCulateCrc8(const u8 * data, int numBits);
};
#endif
