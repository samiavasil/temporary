#include "QFraMeasureCommand.h"
#include "QFraMeasurementContext.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFraMeasureCommand::QFraMeasureCommand( QFraMeasurementContext* context, QObject *parent ):QCommand(parent),m_Ctx(context)
{
}

QFraMeasureCommand::~QFraMeasureCommand(){

}

#include<qtestcommand.h>
#include "qt/QCommandExecutor.h"
#include "qt/QPacketCollector.h"
#include "qt/QPortIO.h"
#include "qt/QPacketCollector.h"
#include "QFraMeasureCommand.h"
int QFraMeasureCommand::handler()
{
   static int count;

   CRITICAL << "QFraMeasureCommand::handler() '" << count << "'" << "  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
   count++;

   QtestCommand* comm =NULL;
   for( int i=0; i<10; i++ )
   {
       comm = new QtestCommand( m_Ctx->getPacketCollector(), m_Ctx->getProtocolPackFactory(),
                                m_Ctx->getCommandExecutor() );

       m_Ctx->getCommandExecutor()->appendCommand(comm);
   }
   if( count >= 20 )
   {
     return 0;
   }
   else
   {
      return 1;
   }
}
