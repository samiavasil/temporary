#ifndef _CPACKET_H
#define _CPACKET_H

#include "global.h"
#include"base/CProtocolPackFactory.h"
class CPacket {
  public:
    CPacket(const pack_id_t & packType, int packLenBytes, int packHdrLenBytes = 2, int packPostFixLenBytes = 2);

    ~CPacket();

    virtual int setData(const u8 * data);

    virtual const u8* data();

    virtual int packLen();

    virtual pack_id_t packType();

    int setBits(int bit_offset, int bit_num, const u8 * data);

    int getBits(int bit_offset, int bit_num, u8 * res_data);


  protected:
    u8* m_data;

    int m_packLenBytes;

    pack_id_t m_packType;


  private:
    int m_hdrLenBytes;

    int m_postFixLenBytes;

};
#endif
