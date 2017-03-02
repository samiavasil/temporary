#ifndef _CPACKET_H
#define _CPACKET_H

#include "global.h"
//#include"base/CProtocolPackFactory.h"

class Q_DECL_EXPORT CPacket {
  public:
    CPacket(const pack_id_t packType, int packLenBit);

    virtual ~CPacket();

    virtual int setData(const u8 * data);

    virtual const u8* data() const;

    virtual int packLenBits() const;

    int packLenBytes() const;

    virtual pack_id_t packType();

    int setBits(int bit_offset, int bit_num, const u8 * data);

    int getBits(int bit_offset, int bit_num, u8 * res_data);


  protected:
    u8* m_data;

    pack_id_t m_packType;

    /**
     * Packet data size in bytes. Should be used for read/write check.
     */
    int m_packLenBits;

};
#endif
