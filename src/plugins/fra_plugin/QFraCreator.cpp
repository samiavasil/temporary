#include "base/global.h"
#include "QFraCreator.h"
#include "QFraFrameWork.h"
#include "QFraIoPortsView.h"
#include "qt/QPacketCollector.h"
#include "qt/QPortIO.h"
#include "qt/QProtocolDb.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QCommandExecutor.h"
#include "qtestcommand.h"
#include "qt/QPluginList.h"
#include <unistd.h>

QFraCreator::QFraCreator(QObject *parent):QCreator(parent),m_qfW( NULL )
{

}

QFraCreator::~QFraCreator( )
{
    if( m_qfW ){
      m_qfW->deleteLater();
    }
}
#include<QStringList>
 #include <QMetaMethod>
#include "qt/QProtocolLoader.h"
bool QFraCreator::Create( CFrameWork *fW )
{
    bool bRet = false;
QPluginList::Instance()->exec();
    if( fW )
    {
        m_qfW =  dynamic_cast<QFraFrameWork*>(fW);
        DEBUG <<   tr("QFraFrameWork[%1]").arg(random());
        if( m_qfW )
        {
            QPortIO* port = NULL;
            QList<PluginDescription> list = QPluginList::Instance()->getAllActivePlugins( UNDEFINED );
            QFraIoPortsView* PIOList = new QFraIoPortsView( m_qfW );
            m_qfW->AddWidgetToControlArrea( PIOList );
            for( int i = 0; i < list.count(); i++ ){
                QObject* obj;
                if(  DATA_OUT == list[i].type() )
                {
                    obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );

                    if( obj )
                    {
                       m_qfW->AddWidgetToDataViewArrea( dynamic_cast<QWidget*>(obj) );
                       const QMetaObject* metaObject = obj->metaObject();

                        DEBUG <<"DUMP METHODS:   "<<endl;
                        for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
                        {
                            DEBUG <<   tr("QFraFrameWork[%1]").arg(random());
                            DEBUG <<"   "<<QString::fromLatin1(metaObject->method(i).signature());
                            if( -1 == metaObject->indexOfSignal( metaObject->method(i).signature() ) )
                            {
                                DEBUG << ":  Method Not signal";
                            }
                            else
                            {
                                DEBUG << ":  Its a signal";
                                if( metaObject->checkConnectArgs ( "testSlot()", metaObject->method(i).signature() ) )
                                {
                                     DEBUG  << "==> Compatible with slot testSlot";
                                }
                                else
                                {
                                    DEBUG  << "==> Not Compatible with slot testSlot";
                                }
                            }

                            DEBUG << endl;
                            //testSlot
                        }
                    }
                }
                if(  PORT_IO == list[i].type() )
                {
                     PIOList->addToList( list[i] );
                }
            }

            port = PIOList->getCurentIO();
            m_qfW->show();

            if( port )
            {
                //TODO Sloji g wsichjki tia obekti da imat parent Qobject (primerno m_qfW) za da moje da se trie lesno
//TODO All object  should be created from Factory

                QProtocolPackFactory* fact    = new QProtocolPackFactory( m_qfW );
                fact->attachProtocolDb( new QProtocolDb() );
                fact->attachProtocol( new QProtocolLoader() );
                QPacketCollector*     colect  = new QPacketCollector( port, fact, m_qfW );
                if( port&&colect ){
                    connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
                }
                //port->showPortConfiguration( NULL );

                QCommandExecutor* pExecutor = new QCommandExecutor( m_qfW );

                if( 0 != pExecutor ){
                    if( NO_ERR != pExecutor->startExecution( true ) ){
                        CRITICAL << "Can't start Executor thread";
                    }
                }
                QObject::connect( m_qfW,SIGNAL(fwDestroy()),pExecutor,SLOT(finish()) ,Qt::DirectConnection );
QtestCommand* comm =NULL;
                for(int i=0;i<1;i++)
                {
                    comm = new QtestCommand( colect, fact, pExecutor);

                    pExecutor->appendCommand(comm);
                }
                sleep(1);//pExecutor->appendCommand(comm);
                pExecutor->pauseExecution(false);
                /*TODO DELL ME*/
               // sleep(1);
               //  pExecutor->startExecution(true);
               //DELL ME set to false to run commands

            }
            bRet = true;
            DEBUG <<   tr("QFraFrameWork[%1]").arg(random());
        }
    }

    return bRet;
}

void QFraCreator::Free()
{

}
