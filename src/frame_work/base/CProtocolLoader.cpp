#include "base/CProtocolLoader.h"
#include "base/CProtocolDb.h"
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

int CProtocolLoader::loadProtocolDefinition(CProtocolDb *protDB) {
int errCode = WRONG_PARAMS;
  if(   protDB ){
      int MsgCount  = 0;                                                                                        
      int PackCount = 0;                                                                                        
      pack_id_t packID;                                                                                         
      msg_id_t  msgID;                                                                                          
      int msgLen;                                                                                               
      int i,j;                                                                                                  
       protDB->clearProtDefinitions();
      errCode = readProtocolData();                                                                             
      if( NO_ERR  == errCode ){                                                                                 
                                                                                                                
          int max_pack_size = getMaxPacketSize( );                                                              
          if( 0 < max_pack_size ){                                                                              
               protDB->setMaxPacketLen( max_pack_size );
          }                                                                                                     
          else{                                                                                                 
              errCode = WRONG_DATA;                                                                             
              CRITICAL << "Error[" << errCode << "]: Can't read packet size";
              return errCode;                                                                                   
          }                                                                                                     
          int lenBits = getHeaderLenBits();                                                                     
          if( 0 < lenBits ){                                                                                    
               protDB->setProtocolHeaderLenBits( lenBits );
          }                                                                                                     
          else{                                                                                                 
              errCode = WRONG_DATA;                                                                             
              CRITICAL << "Error[" << errCode << "]: Can't read packet header size";
              return errCode;                                                                                   
          }                                                                                                     
          lenBits = getPostFixLenBits();                                                                        
          if( 0 <= lenBits ){                                                                                   
               protDB->setProtocolPostFixLenBits( lenBits );
          }                                                                                                     
          else{                                                                                                 
              errCode = WRONG_DATA;                                                                             
              CRITICAL << "Error[" << errCode << "]: Can't read packet post fix size";
              return errCode;                                                                                   
          }                                                                                                     
          MsgCount = getMsgCount();                                                                             
          for( i=0; i < MsgCount;i++ ){                                                                         
              msgID  = getMsgId(i);                                                                             
              if(  MSG_ID_INVALID != msgID ){                                                                   
                  errCode = getMsgIdLen(msgID,&msgLen);                                                         
                  if( NO_ERR == errCode ){                                                                      
                      errCode =  protDB->addMessage( msgID, msgLen );
                      if( NO_ERR != errCode ){                                                                  
                          CRITICAL << "Error[" << errCode << "]:Can't add message ID[" << msgID << "]";
                          return errCode;                                                                       
                      }                                                                                         
                  }                                                                                             
                  else{                                                                                         
                      CRITICAL << "Error[" << errCode << "]:Can't get Len for message ID[" << msgID << "]";
                      return errCode;                                                                           
                  }                                                                                             
              }                                                                                                 
              else{                                                                                             
                  /*TODO Someting*/                                                                             
                  errCode = WRONG_DATA;                                                                         
                  CRITICAL << "TODO: " << __func__ << " : MSG_ID_INVALID";
                  return errCode;                                                                               
              }                                                                                                 
          }                                                                                                     
          PackCount = getPacketCount();                                                                         
                                                                                                                
          for( i=0; i < PackCount;i++ ){                                                                        
              packID = getPackId(i);                                                                            
              if( PKT_ID_INVALID != packID ){                                                                   
                  errCode =  protDB->addPacket( packID );
                  if( NO_ERR != errCode ){                                                                      
                      CRITICAL << "Error[" << errCode << "]:Can't add packet ID[" << packID << "]";
                      return errCode;                                                                           
                  }                                                                                             
                                                                                                                
                  MsgCount = getMsgsCountForPack( packID );                                                     
                  if( ( 0 < MsgCount )&&( max_pack_size > MsgCount ) ){                                         
                      for( j = 0; j < MsgCount; j++ ){                                                          
                          msgID = getMsgIdForPack( packID, j );                                                 
                          if( MSG_ID_INVALID != msgID ){                                                        
                              errCode =  protDB->addMessageToPacket( packID, msgID );
                              if( NO_ERR != errCode ){                                                          
                                  CRITICAL << "Error[" << errCode << "]:Invalid Message ID[" << msgID << "]";
                                  return errCode;                                                               
                              }                                                                                 
                          }                                                                                     
                          else{                                                                                 
                              CRITICAL <<  "Error[" << errCode << "]:Invalid Message ID["<< msgID
                                       <<  "] for pack ID[" << packID << "]";
                          }                                                                                     
                      }                                                                                         
                  }                                                                                             
                  else{                                                                                         
                      /*TODO Someting*/                                                                         
                      if( 0 >= MsgCount ){
                          CRITICAL << "TODO: " << __func__ << " : Packet without messages";
                      }                                                                                         
                      else{                                                                                     
                          CRITICAL << "TODO: " << __func__ << " : Max messages in packet limit is exceeded";
                      }                                                                                         
                  }                                                                                             
              }                                                                                                 
          }                                                                                                     
      }                                                                                                         
  }

  return errCode;                                                                                               
}

