#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include <qglobal.h>

typedef qint8    int8;
typedef qint16   int16;
typedef qint32   int32;
typedef qint64   int64;
typedef quint8   u8;
typedef quint16  u16;
typedef quint32  u32;
typedef quint64  u64;

enum{
	NO_ERR,
    WRONG_PARAMS,
    WRONG_DATA,
    NULL_POINTER,
    SOME_ERROR
};



/* Calculate number of bytes needed for X bits */
#define BITS_TO_BYTES_CEIL(x) (( x/8 ) + (( x%8 )?1:0))
#define BIT_MASK_BEFORE_BIT_U8( x )  (( ( 1 << x ) - 1  )&0xff)
#define BIT_MASK_AFTER_BIT_U8( x )   ((~BIT_MASK_BEFORE_BIT_U8( x ))&0xff)

#define MASK_OFF_LEN( offset,len )   ((((1<<len)-1)&0xff) >> offset)

/* src_off,dest_off should be 0:7
   bitnum 1:8
*/
#define MOVE_SRC_TO_DEST_BITS_IN_BYTE( src,dest,src_off,dest_off,bitnum )  if( bitnum ){\
    dest &= ( ~MASK_OFF_LEN( (dest_off), (bitnum) ) );/*Clear destination bits*/\
    dest |= ( ( (src)&MASK_OFF_LEN( (src_off), (bitnum) )<<(src_off) ) >> (dest_off) );\
    }

#endif
