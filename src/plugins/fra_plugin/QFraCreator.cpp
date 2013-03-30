#include "QFraCreator.h"
#include "qt/QFrameWork.h"
#include <ui_qfra_frame_work_view.h>
#include "qt/QPacketCollector.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QProtocolLoader.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QCommandExecutor.h"
#include "qtestcommand.h"



QFraCreator::QFraCreator(QObject *parent):QCreator(parent)
{

}

QFraCreator::~QFraCreator( )
{

}

bool QFraCreator::Create( CFrameWork *fW )
{
   bool bRet = false;

    if( fW )
    {
       QFrameWork* qfW =  dynamic_cast<QFrameWork*>(fW);
        if( qfW )
        {
            DEBUG("%d\n", qfW->metaObject()->indexOfSignal("destroyed"));
               Ui::QFraFrameWorkView * ui = new Ui::QFraFrameWorkView;
               ui->setupUi(qfW);
               qfW->show();
               QPortIOSimulator* port      = new QPortIOSimulator( qfW );
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
                   pExecutor->pauseExecution(false);

            }
            bRet = true;

        }
    }

    return bRet;
}

void QFraCreator::Free()
{

}
