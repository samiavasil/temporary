#include "qtestcommand.h"

#include "base/CPacket.h"
#include "base/CPacketCollector.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QProtocolLoader.h"
#include<stdio.h>
#include"qt/QPacketCollector.h"

#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"




pack_id_t pId[4]={
    AIN_CFG_ID,
    EN_DREC_ID,
    DREC_SET_CFG_ID,
    DREC_SET_FREQ_ID
};

#include "qt/QRegFactory.h"
#include "qt/QCommandExecutor.h"
QtestCommand::QtestCommand( QPacketCollector* colector, QProtocolPackFactory *factory, QObject *par ):QCommand(par) {
    m_Col     = colector;
    m_Factory = factory;
    exec = dynamic_cast<QCommandExecutor*>(par);
    a=0;
    DEBUG << "QtestCommand Created";
}

QtestCommand::~QtestCommand() {
  DEBUG << "QtestCommand Deleted";
}


/**
 * Command handler
 */
int QtestCommand::handler() {
  int ret =  1;

#if 0 //TODO - DELL ME
  fact1_t::Registrator<A>  rep( tr("Blqk %1").arg(rand()) );

  QSet<QString> outlist;
  fact1_t::GetRegList(outlist);
  qDebug()<<outlist;
#endif


  CPacket* packet = NULL;
  DEBUG <<   tr("Bliak[%1]").arg(a);
  if( a >= 1 ){
      a = 0;
      ret =  0;
      DEBUG << "QCommand Finished=====================================";
#if 0
      if(exec)
      exec->appendCommand(new QtestCommand( m_Col, m_Factory, exec));
      else
          DEBUG << "CAN'T APPEND COMMMANNDDDD";
#endif
  }
  else
  {
      if( 1 ){//a == 0 ){
          //DEBUG << "QCommand Execution start");

          if( m_Factory ){
              a = 0;
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
