#include "qt/QCommand.h"
#include "qt/QFrameWork.h"
#include "base/CPacket.h"
#include "base/CPacketCollector.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include<stdio.h>
pack_id_t pId[4]={
    PACK1_ID,
    PACK2_ID,
    PACK3_ID,
    PACK4_ID,
};

QCommand::QCommand( QFrameWork * fWork ) {
  m_fWork = fWork;
  a=0;         
}

QCommand::~QCommand() {
  DEBUG("QCommand Deleted");
}

/**
 * Command handler
 */
int QCommand::handler() {
    int ret =  1;
    CPacket* packet = NULL;
    
    if( a >= 0 ){
        ret =  0;
     //  DEBUG("QCommand Finished");
    }
    else{
        if( 1 ){//a == 0 ){
            //DEBUG("QCommand Execution start");
            QProtocolPackFactory *factory =  (QProtocolPackFactory*)m_fWork->getProtocol();
            if(factory){
                packet = factory->createPacket( pId[a%4] );
            }
        }
        if( m_fWork&&packet ){
            CPacketCollector* colector = m_fWork->getColector();
            if( colector ){
                colector->transmitPacket( packet );
                DEBUG("TRANSMIT PACKET[%d] num[%d]",packet->packType(),a);
                if( packet ){
                    const u8*data = packet->data();
                    for( int i=0;i < packet->packLenBytes();i++ ){
                        fprintf(stderr," %02x",data[i]);
                    }
                    fprintf(stderr,"\n\n");
                }
            }
        }
        if(packet){
            delete packet;
        }
    }
    a++;
    return ret;
}

