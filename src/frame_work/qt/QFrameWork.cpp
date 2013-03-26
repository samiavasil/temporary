
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QPacketCollector.h"
#include "qt/QPluginList.h"

QFrameWork::QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent) :QWidget( parent),CFrameWork( factory)
{
  QPacketCollector* colect = dynamic_cast<QPacketCollector*> (m_Colector);
  QPortIO* port = dynamic_cast<QPortIO*> (m_PortIO);
  if( port&&colect ){
      connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
  }
}

QFrameWork::QFrameWork( QCreator* creator , QWidget * parent ):QWidget( parent),CFrameWork( creator )
{

}

QFrameWork::~QFrameWork()
{
  DEBUG("Destroy QFrameWork");
}

QList<QObject*>  QFrameWork::CreateObjectFromType( )
{
    QList<QObject*> ret_List;
    QList<QPluginDescriptor *> list;

    list = QPluginList::Instance()->getAllActivePlugins( DATA_PLOT );

    for( int i = 0; i < list.count(); i++ ){
        if( list[i] &&  ( list[i]->type() == DATA_PLOT ) ){
            ret_List.append( list[i]->cretate_plugin_object( list[i]->type() , NULL ) );//DELL ME
        }

    }
    return ret_List;
}
