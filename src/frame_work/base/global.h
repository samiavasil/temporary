#ifndef __GLOBAL_H__
#define __GLOBAL_H__

typedef  short int          int8;
typedef  short int          int16;
typedef  int                   int32;
typedef long long int     int64;
typedef unsigned char  u8;
typedef unsigned short int u16;
typedef unsigned int     u32;

enum{
	NO_ERR,
    WRONG_PARAMS,
    WRONG_DATA,
    NULL_POINTER,
    SOME_ERROR
};

/*TODO: FIX ME*/
#include  <QtGlobal>
#define DEBUG    qDebug
#define CRITICAL qCritical
#define FATAL    qFatal

/* Calculate number of bytes needed for X bits */
#define  BITS_TO_BYTES_CEIL(x) (( x/8 ) + (( x%8 )?1:0))
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
