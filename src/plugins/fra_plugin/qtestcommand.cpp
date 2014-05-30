#include "qtestcommand.h"

#include "base/CPacket.h"
#include "base/CPacketCollector.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include<stdio.h>
#include"qt/QPacketCollector.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"




pack_id_t pId[4]={
    AIN_CFG_ID,
    EN_DREC_ID,
    DREC_SET_CFG_ID,
    DREC_SET_FREQ_ID
};

QtestCommand::QtestCommand( QPacketCollector* colector, QProtocolPackFactory *factory, QObject *parent ):QCommand(parent) {
    m_Col     = colector;
    m_Factory = factory;
    a=0;
    DEBUG << "QtestCommand Created";
}

QtestCommand::~QtestCommand() {
  DEBUG << "QtestCommand Deleted";
}


#include "qt/QRegFactory.h"

/**
 * Command handler
 */
int QtestCommand::handler() {
  int ret =  1;
 fact1_t::Registrator<A>  rep( tr("Blqk %1").arg(rand()) );

  QSet<QString> outlist;
  fact1_t::GetRegList(outlist);
  qDebug()<<outlist;



  CPacket* packet = NULL;
  DEBUG <<   tr("Bliak[%1]").arg(a);
  if( a >= 1 ){
      ret =  0;
      DEBUG << "QCommand Finished";
  }
  else
  {
      if( 1 ){//a == 0 ){
          //DEBUG << "QCommand Execution start");

          if( m_Factory ){
              packet = m_Factory->createPacket( pId[a%4] );
          }
      }
      if( packet ){

          if( m_Col ){

              if( 0 < m_Col->transmitPacket( packet ) ){
                  DEBUG << "TRANSMIT PACKET[" << packet->packType() << "] num[" << a << "]";
                  if( packet ){
                      fprintf( stderr," Transmit Packet[%d]: Data is:\n",packet->packType() );
                      const u8*data = packet->data();
                      for( int i=0;i < packet->packLenBytes();i++ ){
                          fprintf(stderr," %02x",data[i]);
                      }
                      fprintf(stderr,"\n\n");
                  }
              }
              else{
                  DEBUG << "!!!TRANSMIT ERRORR: PACKET[" << packet->packType() << "] num[" << a << "]";
              }
          }

      }

  }
  a++;
  return ret;
}
