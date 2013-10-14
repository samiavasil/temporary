#include "qtestcommand.h"

#include "base/CPacket.h"
#include "base/CPacketCollector.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include "qt/debug.h"

#include<stdio.h>
#include"qt/QPacketCollector.h"

pack_id_t pId[4]={
    PACK1_ID,
    PACK2_ID,
    PACK3_ID,
    PACK4_ID,
};

QtestCommand::QtestCommand( QPacketCollector* colector, QProtocolPackFactory *factory, QObject *parent ):QCommand(parent) {
    m_Col     = colector;
    m_Factory = factory;
    a=0;
    DEBUG("QtestCommand Created");
}

QtestCommand::~QtestCommand() {
  DEBUG("QtestCommand Deleted");
}

/**
 * Command handler
 */
int QtestCommand::handler() {
  int ret =  1;
  CPacket* packet = NULL;
  DEB1(  tr("Bliak[%1]").arg(a) );
  if( a >= 1 ){
      ret =  0;
      //  DEBUG("QCommand Finished");
  }
  else{
      if( 1 ){//a == 0 ){
          //DEBUG("QCommand Execution start");

          if( m_Factory ){
              packet = m_Factory->createPacket( pId[a%4] );
          }
      }
      if( packet ){

          if( m_Col ){
              if( 0 < m_Col->transmitPacket( packet ) ){
                  DEBUG("TRANSMIT PACKET[%d] num[%d]",packet->packType(),a);
                  if( packet ){
                      const u8*data = packet->data();
                      for( int i=0;i < packet->packLenBytes();i++ ){
                          fprintf(stderr," %02x",data[i]);
                      }
                      fprintf(stderr,"\n\n");
                  }
              }
              else{
                  DEBUG("!!!TRANSMIT ERRORR: PACKET[%d] num[%d]",packet->packType(),a);
              }
          }

      }

  }
  a++;
  return ret;
}
