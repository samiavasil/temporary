#include "QFraCreator.h"
#include "QFraFrameWork.h"
#include "qt/QPacketCollector.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QProtocolLoader.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QCommandExecutor.h"
#include "qtestcommand.h"
#include "qt/QPluginList.h"


QFraCreator::QFraCreator(QObject *parent):QCreator(parent)
{

}

QFraCreator::~QFraCreator( )
{

}
#include "qt/QSerialPortIO.h"
bool QFraCreator::Create( CFrameWork *fW )
{
   bool bRet = false;

    if( fW )
    {
       QFraFrameWork* qfW =  dynamic_cast<QFraFrameWork*>(fW);
        if( qfW )
        {
                  QSerialPortIO* portSer = NULL;
                  QList<PluginDescription> list = QPluginList::Instance()->getAllActivePlugins( UNDEFINED );

                 for( int i = 0; i < list.count(); i++ ){
                     QObject* obj;
                     if(  DATA_PLOT == list[i].type() )
                     {
                         obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );
                         /*ui->verticalLayout->addWidget(dynamic_cast<QWidget*>(obj));
                         if( obj ){
                             dynamic_cast<QWidget*>(obj)->show();//DELL ME
                         }*/
                         qfW->AddWidgetToDataViewArrea( dynamic_cast<QWidget*>(obj) );
                     }
                     if(  PORT_IO == list[i].type() )
                     {
                         obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );

                          portSer =    dynamic_cast<QSerialPortIO*>(obj);//DELL ME

                          if( portSer )
                          {
                              QWidget* widg = new QWidget( qfW );
                              qfW->AddWidgetToControlArrea( widg );
                              portSer->showPortConfiguration(widg);
                          }
                     }
                 }


               qfW->show();
               QPortIO* port = NULL;
               if( portSer )
               {
                  port = portSer;
               }
               else
               {
                  port = new QPortIOSimulator( qfW );
               }
               if( port )
               {
                   //TODO Sloji g wsichjki tia obekti da imat parent Qobject (primerno qfW) za da moje da se trie lesno

                   QProtocolLoader     * pLoader = new QProtocolLoader();
                   QProtocolPackFactory* fact    = new QProtocolPackFactory( pLoader, qfW );
                   QPacketCollector*     colect  = new QPacketCollector( port, fact, qfW );
                   if( port&&colect ){
                       connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
                   }
                   //port->showPortConfiguration( NULL );
                   delete pLoader;
                   QCommandExecutor* pExecutor = new QCommandExecutor( qfW );

                   if( 0 != pExecutor ){
                       if( NO_ERR != pExecutor->startExecution( true ) ){
                           CRITICAL( "Can't start Executor thread" );
                       }
                   }
                   QtestCommand* comm = new QtestCommand( colect, fact, pExecutor);
                   QObject::connect( qfW,SIGNAL(fwDestroy()),pExecutor,SLOT(finish()) ,Qt::DirectConnection );
                   pExecutor->appendCommand(comm);
                   /*TODO DELL ME*/
                   sleep(1);
                  // pExecutor->startExecution(true);
                   pExecutor->pauseExecution(false);//DELL ME set to false to run commands

            }
            bRet = true;

        }
    }

    return bRet;
}

void QFraCreator::Free()
{

}
