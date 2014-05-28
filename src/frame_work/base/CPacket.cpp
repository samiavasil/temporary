#include "base/CPacket.h"
#include <string.h>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

CPacket::CPacket(const pack_id_t packType, int packLenBit) {
  DEBUG << "Create Packet[" << packType << "] - Bit size = " << packLenBit;
  m_packType        = packType;                                                              
  m_packLenBits     = packLenBit;                                                            
  if( 0 < m_packLenBits ){                                                                   
    m_data = new u8[BITS_TO_BYTES_CEIL(m_packLenBits)];    
    memset( m_data,0,BITS_TO_BYTES_CEIL(m_packLenBits) );  
  }                                                                                          
  else{                                                                                      
    CRITICAL <<  "Can't memory allocate Packet[" << m_packType << "] - Bit size =" <<  m_packLenBits;
    m_packType = PKT_ID_INVALID;                                                             
    m_data = NULL;                                                                           
  }                                                                                          
}

CPacket::~CPacket() {
    DEBUG << "Destroy Packet[" << m_packType << "]";
  if( m_data ){        
      delete [] m_data;
  }                    
}

int CPacket::setData(const u8 * data) {
  int ret = NO_ERR;                                                
  if( data )                                                       
  {                                                                
      memcpy( m_data, data, BITS_TO_BYTES_CEIL(m_packLenBits) );   
  }                                                                
  else{                                                            
      ret = WRONG_PARAMS;                                          
  }                                                                
  return ret;                                                      
}

const u8* CPacket::data() const {
  return m_data;
}

int CPacket::packLenBits() const {
  return m_packLenBits;
}

int CPacket::packLenBytes() const {
  return BITS_TO_BYTES_CEIL(m_packLenBits);
}

pack_id_t CPacket::packType() {
  return m_packType;
}

int CPacket::setBits(int bit_offset, int bit_num, const u8 * data) {
  int ret = NO_ERR;

  int byte_offset    = bit_offset/8;                                                
  int offset_in_byte = bit_offset%8;                                                
  int bytes_num      = BITS_TO_BYTES_CEIL( bit_num);
  int i = 0;                                                                        
                                                                                    
  if(  ( 0 > bit_offset )||( 0 > bit_num )||
       ( m_packLenBits < ( bit_offset + bit_num ) )||
       ( NULL == data )
    )
  {
      return WRONG_PARAMS;
  }
#if 1
  int ctr = bit_num;
  int dest_offset = bit_offset;
  u16 d_in;
  int bits_in_d_in;


  int bit_remind_src = bit_num%8;
  int src_start  = (8 -( bit_remind_src ))%8;
  int src_cur    = src_start;
  int dest_idx;
  int need_bits;
  if( !bit_remind_src ){
      d_in         = data[0];
      if( bit_num < 8 )
      {
         bits_in_d_in = bit_num;
         d_in         = data[0]&BIT_MASK_BEFORE_BIT_U8( bit_num );
      }
      else
      {
         bits_in_d_in = 8;
      }
  }
  else{
      d_in         = data[0]&BIT_MASK_BEFORE_BIT_U8( bit_remind_src );
      bits_in_d_in = bit_remind_src;
  }

  src_cur += bits_in_d_in;

  while( ctr > 0 )
  {
      need_bits   = 8 - (dest_offset%8);
      if( need_bits > ctr )
      {
         need_bits = ctr;
      }
      //get and set needed bits
      if( bits_in_d_in < need_bits ){
          int more_bits =  need_bits - bits_in_d_in;
          bit_remind_src    = 8 - (src_cur%8);
          if( bit_remind_src  <  more_bits )
          {
             u16 c_d = data[ src_cur/8 ] & MASK_OFF_LEN( 0, bit_remind_src );
             d_in  |= ( c_d << bits_in_d_in);
             bits_in_d_in += bit_remind_src;
             src_cur      += bit_remind_src;
          }
          if( !(src_cur%8) )
          {
             u16 c_d = data[ src_cur/8 ];
             d_in  |= ( c_d << bits_in_d_in);
             bits_in_d_in += 8;
             src_cur      += 8;
          }
      }

      dest_idx = dest_offset/8;

      m_data[ dest_idx ] &= (~MASK_OFF_LEN(  0, need_bits ));
      m_data[ dest_idx ] |= ( (d_in&BIT_MASK_BEFORE_BIT_U8(need_bits)) << ( 8 - need_bits - (dest_offset%8)));

      d_in = d_in >> need_bits;
      bits_in_d_in -=     need_bits;

      dest_offset += need_bits;
      ctr         -= need_bits;
  }

#else
                                                                                    
  if( 0 != (bit_offset%8) ){                                                        
      if( 0 < bit_num ){                                                            
          u16 shifter = 0;                                                          
          shifter    = (data[0] << offset_in_byte);                                 
          if( bit_num > ( 8 - offset_in_byte ) ){                                   
              m_data[byte_offset] &= (BIT_MASK_BEFORE_BIT_U8( offset_in_byte ));    
              m_data[byte_offset] |= (shifter&0xff);                                
              bit_num   -= (8-offset_in_byte);                                      
              if( 1 < bytes_num ){                                                  
                                                                                    
                  for( i = 0;i < bytes_num-1;i++ ){                                 
                      shifter   >>= offset_in_byte;                                 
                      shifter    |= (data[i+1]<<8);                                 
                      shifter   >>= (8-offset_in_byte);                             
                      m_data[i+1+byte_offset] =   shifter&0xff;                     
                      bit_num  -= 8;                                                
                  }                                                                 
                  shifter >>= 8 ;                                                   
              }                                                                     
              else{                                                                 
                  shifter >>= ( offset_in_byte + (8-offset_in_byte) );              
              }                                                                     
              if( 0 < bit_num ){                                                    
                  shifter   &= BIT_MASK_BEFORE_BIT_U8( bit_num );                   
                  m_data[i+1+byte_offset] &= (BIT_MASK_AFTER_BIT_U8( bit_num ));    
                  m_data[i+1+byte_offset] |= shifter;                               
              }                                                                     
          }                                                                         
          else{

//#define MASK_OFF_LEN( offset,len )   ((((1<<len)-1)&0xff) << offset)
              m_data[byte_offset] &= (~MASK_OFF_LEN( offset_in_byte, bit_num ));
              m_data[byte_offset] |= (shifter&MASK_OFF_LEN( offset_in_byte, bit_num ));
//              m_data[byte_offset] &= (BIT_MASK_BEFORE_BIT_U8( offset_in_byte ));

//              m_data[byte_offset] |= (shifter&0xff);
          }                                                                         
      }                                                                             
  }                                                                                 
  else{                                                                             
      int remainder = (bit_num%8);                                                  
      /*For high speed when offset are byte alligned*/                              
      for( i=0; i < (bytes_num-1); i++ ){                                           
          m_data[i+byte_offset] = data[i];                                          
      }                                                                             
      if( 0 ==  remainder ){                                                        
          m_data[i+byte_offset] = data[i];                                          
      }                                                                             
      else{                                                                         
    //      m_data[i+byte_offset] &= BIT_MASK_AFTER_BIT_U8( remainder );
     //     m_data[i+byte_offset] |= ((data[i])&BIT_MASK_BEFORE_BIT_U8( remainder ));

          m_data[i+byte_offset] &= (~MASK_OFF_LEN( 0, remainder ));
          m_data[i+byte_offset] |= (data[i]&MASK_OFF_LEN( 0, remainder ));
      }                                                                             
                                                                                    
  }
#endif

  return ret;                                                                       
}

int CPacket::getBits(int bit_offset, int bit_num, u8 * res_data) {
  int ret = NO_ERR;                                                                               
  int byte_offset    = bit_offset/8;                                                              
  int offset_in_byte = bit_offset%8;                                                              
  int bytes_num      = BITS_TO_BYTES_CEIL( bit_num );                                             
  int i = 0;                                                                                      
                                                                                                  
  if( ( 0 > bit_offset )||( 0 > bit_num )||(NULL == res_data) ){                                  
      return WRONG_PARAMS;                                                                        
  }                                                                                               
  if( 0 != (bit_offset%8) ){                                                                      
                                                                                                  
      if( 0 < bit_num ){                                                                          
          u16 shifter = 0;                                                                        
          shifter    = ( m_data[ byte_offset ] ) & BIT_MASK_AFTER_BIT_U8( offset_in_byte );       
          if( bit_num > ( 8 - offset_in_byte ) ){                                                 
                                                                                                  
              for( i = 0; i < bytes_num-1; i++ ){                                                 
                  shifter      |= ( ( m_data[ byte_offset + i + 1 ] )<<8 );                       
                  shifter     >>= offset_in_byte;                                                 
                  res_data[i]   = shifter&0xff;                                                   
                  shifter     >>= (8 - offset_in_byte);                                           
                  bit_num      -= 8;                                                              
              }                                                                                   
              shifter      |= ( ( m_data[ byte_offset + i + 1 ] )<<8 );                           
          }                                                                                       
          if( 0 < bit_num ){                                                                      
              shifter   >>= offset_in_byte;                                                       
              res_data[i] = shifter & BIT_MASK_BEFORE_BIT_U8( bit_num );                          
          }                                                                                       
      }                                                                                           
  }                                                                                               
  else{                                                                                           
      int remainder = (bit_num%8);                                                                
      /*For high speed when offset are byte alligned*/                                            
      for( i=0; i < (bytes_num-1); i++ ){                                                         
          res_data[i] = m_data[i+byte_offset];                                                    
      }                                                                                           
      if( 0 ==  remainder ){                                                                      
          res_data[i] = m_data[i+byte_offset];                                                    
      }                                                                                           
      else{                                                                                       
          (res_data[i])  = 0;                                                                     
          (res_data[i]) |= ( (m_data[ i + byte_offset ])&BIT_MASK_BEFORE_BIT_U8( remainder ) );   
      }                                                                                           
                                                                                                  
  }                                                                                               
  return ret;                                                                                     
}

