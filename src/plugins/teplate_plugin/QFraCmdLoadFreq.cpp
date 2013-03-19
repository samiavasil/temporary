#define ENBLE_DEBUG
#include "target/fra/QFraCmdLoadFreq.h"
#include "target/fra/QFraProtocolPacketsFabrique.h"
#include "basic/QFrameWork.h"

int QFraCmdLoadFreq::number;

/**
   @brief       

   @param      

   Description:  

   @pre 
   
   @return
     
   @note
   @see         
 */

QFraCmdLoadFreq::QFraCmdLoadFreq(QObject * parent):QCommand( parent ) {
  m_state = LF_INIT;
  number++;
  local_number = number;
}

/**
   @brief       

   @param      

   Description:  

   @pre 
   
   @return
     
   @note
   @see         
 */

bool QFraCmdLoadFreq::handler(QFrameWork * frame_work) {
    bool bRet = true;
     DEBUG("RUN LOAD FREQ");
     switch( m_state ){
     case LF_INIT:{
             m_state = LF_SEND_FEQ;
             break;
         }
     case LF_SEND_FEQ:{
             for(int i=0;i < 8;i++)
             frame_work->sendPacket( i, QByteArray() );
             m_state  = LF_WAIT_ACK;
             break;
         }
     case LF_WAIT_ACK:{
             QPacketCollector* pac_col =  frame_work->getPacketCollector();
             if( pac_col && pac_col->getRecPacketsNum() ){}
                 QPacket* pack =  pac_col->findRecPacket( 3 );
                 if( NULL !=  pack ){  //ACK == pack->ack() ){
                     DEBUG("Packet [%d] founded",pack->packType());
                     m_state = LF_INIT;
                     bRet = false;
                 }

             break;
         }
     default:{
             m_state = LF_INIT;
             break;
         }        
     }
     return bRet;
  
}

