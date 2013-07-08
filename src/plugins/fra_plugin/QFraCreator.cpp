#include "QFraCreator.h"
#include "QFraFrameWork.h"
#include "QFraIoPortsView.h"
#include "qt/QPacketCollector.h"
#include "qt/QPortIO.h"
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
#include<QStringList>
 #include <QMetaMethod>
bool QFraCreator::Create( CFrameWork *fW )
{
    bool bRet = false;

    if( fW )
    {
        QFraFrameWork* qfW =  dynamic_cast<QFraFrameWork*>(fW);
        if( qfW )
        {
            QPortIO* port = NULL;
            QList<PluginDescription> list = QPluginList::Instance()->getAllActivePlugins( UNDEFINED );
            QFraIoPortsView* PIOList = new QFraIoPortsView( qfW );
            qfW->AddWidgetToControlArrea( PIOList );
            for( int i = 0; i < list.count(); i++ ){
                QObject* obj;
                if(  DATA_OUT == list[i].type() )
                {
                    obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );

                    qfW->AddWidgetToDataViewArrea( dynamic_cast<QWidget*>(obj) );

                    if( obj )
                    {
                       const QMetaObject* metaObject = obj->metaObject();

                        qDebug()<<"DUMP METHODS:   "<<endl;
                        for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
                        {

                            qDebug()<<"   "<<QString::fromLatin1(metaObject->method(i).signature());
                            if( -1 == metaObject->indexOfSignal( metaObject->method(i).signature() ) )
                            {
                                qDebug() << ":  Method Not signal";
                            }
                            else
                            {
                                qDebug() << ":  Its a signal";
                                if( metaObject->checkConnectArgs ( "testSlot()", metaObject->method(i).signature() ) )
                                {
                                     qDebug() << "==> Compatible with slot testSlot";
                                }
                                else
                                {
                                    qDebug() << "==> Not Compatible with slot testSlot";
                                }
                            }

                            qDebug()<<endl;
                            //testSlot
                        }
                    }
                }
                if(  PORT_IO == list[i].type() )
                {
                    obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );
                    port =    dynamic_cast<QPortIO*>(obj);//DELL ME
                    if( port )
                    {
                        port->deleteLater();
                        PIOList->addToList( list[i] );
                    }
                }
            }

            port = PIOList->getCurentIO();
            qfW->show();

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
