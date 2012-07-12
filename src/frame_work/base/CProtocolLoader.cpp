
#include "base/CProtocolLoader.h"

int CProtocolLoader::loadProtocolDefinition(CProtocolPackFactory * protoFactory) {
  int errCode = WRONG_PARAMS;                                                                       
  if(  protoFactory ){                                                                              
      int MsgCount  = 0;                                                                            
      int PackCount = 0;                                                                            
      pack_id_t packID;                                                                             
      msg_id_t  msgID;                                                                              
      int i,j;                                                                                      
      errCode = readProtocolData();                                                                 
      if( NO_ERR  == errCode ){                                                                     
                                                                     
          int max_pack_size = getMaxPacketSize( );                           
          if( 0 < max_pack_size ){                                           
            protoFactory->setMaxPacketSize( max_pack_size );               
          }                                                                  
          else{                                                              
            errCode = WRONG_DATA;                                          
            CRITICAL( "Error[%d]: Can't read packet size",errCode );       
            return errCode;                                                
          }                                                                                                                                                                                                   
          MsgCount = getMsgCount();                                                                 
          for( i=0; i < MsgCount;i++ ){                                                             
              msgID = getMsgId(i);                                                                    
              if(  MSG_ID_INVALID != msgID ){                                                       
                  errCode = protoFactory->addMessage( msgID );
                  if( NO_ERR != errCode ){                                                          
                      CRITICAL( "Error[%d]:Can't add message ID[%d]",errCode,msgID );               
                      return errCode;                                                               
                  }                                                                                 
              }                                                                                     
              else{                                                                                 
                  /*TODO Someting*/                                                                 
                  CRITICAL("TODO: %s : MSG_ID_INVALID",__func__);                                   
              }                                                                                     
          }                                                                                         
          PackCount = getPacketCount();                                                             
                                                                                                    
          for( i=0; i < PackCount;i++ ){                                                            
              packID = getPackId(i);                                                                
              if( PKT_ID_INVALID != packID ){                                                      
                  errCode = protoFactory->addPacket( packID );                                      
                  if( NO_ERR != errCode ){                                                          
                      CRITICAL( "Error[%d]:Can't add packet ID[%d]",errCode, packID );              
                      return errCode;                                                               
                  }                                                                                 
                                                                                                    
                  MsgCount = getMsgsCountForPack( packID );                                         
                  if( ( 0 < MsgCount )&&( max_pack_size > MsgCount ) ){                             
                      for( j = 0; j < MsgCount; j++ ){                                              
                          msgID = getMsgIdForPack( packID, j );                                     
                          if( MSG_ID_INVALID != msgID ){                                            
                              errCode = protoFactory->addMessageToPacket( packID, msgID );          
                              if( NO_ERR != errCode ){                                              
                                  CRITICAL( "Error[%d]:Invalid Message ID[%d]",errCode,msgID );     
                                  return errCode;                                                   
                              }                                                                     
                          }                                                                         
                          else{                                                                     
                              CRITICAL( "Error[%d]:Invalid Message ID[%d] for pack ID[%d]"          
                                        ,errCode,msgID,packID );                                    
                          }                                                                         
                      }                                                                             
                  }                                                                                 
                  else{                                                                             
                      /*TODO Someting*/                                                             
                      if( 0 >= MsgCount ){                                                          
                          CRITICAL("TODO: %s : Packet without messages",__func__);                  
                      }                                                                             
                      else{                                                                         
                          CRITICAL("TODO: %s : Max messages in packet limit is exceeded",__func__); 
                      }                                                                             
                  }                                                                                 
              }                                                                                     
          }                                                                                         
      }                                                                                             
  }                                                                                                 
  return errCode;                                                                                   
}

