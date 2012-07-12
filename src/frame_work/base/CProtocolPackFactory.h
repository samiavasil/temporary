#ifndef _CPROTOCOLPACKFACTORY_H
#define _CPROTOCOLPACKFACTORY_H


#include "global.h"
typedef int pack_id_t;
typedef int msg_id_t;

#define  PACK_ID_TYPE_BIT_SIZE  (sizeof(pack_id_t)*8)
#define  MSG_ID_TYPE_BIT_SIZE    (sizeof(msg_id_t)*8)
#define  PKT_ID_INVALID   (  (  (1<<(PACK_ID_TYPE_BIT_SIZE-1) ) - 1  )|(PACK_ID_TYPE_BIT_SIZE-1)  )
#define  MSG_ID_INVALID     (  (  (1<<(MSG_ID_TYPE_BIT_SIZE-1) )  - 1  )|(MSG_ID_TYPE_BIT_SIZE-1)  )

class CProtocolLoader;
class CPacket;

class CProtocolPackFactory {
  public:
    CProtocolPackFactory(CProtocolLoader * pLoader);


  protected:
    virtual int clearMsgDefinitions();

    virtual int clearProtDeinfitions();


  public:
    virtual int addPacket(const pack_id_t & id);

    virtual int addMessage(const msg_id_t & id);

    virtual int addMessageToPacket(const pack_id_t & packID, const msg_id_t & msgID);

    virtual int addPacketHeader();

    virtual int addPacketPostFix();

    virtual int createPacket();

    virtual int createPacketFromData();

    virtual int findPacketStart();

    virtual int getMaxPacketSize();

    virtual int getPacketLen();

    virtual int getPacketType();

    virtual int getProtocolHeaderSize();

    virtual int setProtocolHeaderSize();

    virtual int getProtocolPostFixLen();

    virtual int setProtolPostFixLen();

    virtual int setMaxPacketSize(int max_size);

    virtual int setMessage();

};
#endif
