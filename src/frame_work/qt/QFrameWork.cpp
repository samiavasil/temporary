
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QPacketCollector.h"
#include "qt/QPluginList.h"

QFrameWork::QFrameWork( QCreator* creator , QWidget * parent ):QWidget( parent),CFrameWork( creator )
{
    DEBUG( "Create QFrameWork\n" );
    setAttribute(Qt::WA_DeleteOnClose, true);
    if( !Create() )
        deleteLater();
}

QFrameWork::~QFrameWork()
{
  DEBUG( "Destroy QFrameWork\n" );
  if( m_creator )
  {
      delete m_creator;
      m_creator = 0;
  }
}

QList<QObject*>  QFrameWork::CreateObjectFromType(QObject* parent )
{
    QList<QObject*> ret_List;
    QList<QPluginDescriptor *> list;

    list = QPluginList::Instance()->getAllActivePlugins( DATA_PLOT );

    for( int i = 0; i < list.count(); i++ ){
        if( list[i] &&  ( list[i]->type() != FRAME_WORK ) ){
            ret_List.append( list[i]->cretate_plugin_object( list[i]->type() , parent ) );//DELL ME
        }

    }
    return ret_List;
}
