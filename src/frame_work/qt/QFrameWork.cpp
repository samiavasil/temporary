
#include "qt/QFrameWork.h"
#include "qt/QCreator.h"
#include <QObject>


#include "qt/QPluginList.h"
QFrameWork::QFrameWork(QCreator * creator, QWidget * parent):CFrameWork(creator),QWidget(parent){
  DEBUG( "Create QFrameWork\n" );
  setAttribute(Qt::WA_DeleteOnClose, true);
}

QFrameWork::~QFrameWork() {
  DEBUG( "Destroy QFrameWork\n" );
    emit fwDestroy();
    if( m_creator )
    {
       delete m_creator;
        m_creator = 0;
    }
}

bool QFrameWork::Create() {
  return m_creator->Create( this );
}

QList<QObject*> QFrameWork::CreateObjectFromType(QObject * parent) {
      QList<QObject*> ret_List;
      QList<PluginDescription> list;

      list = QPluginList::Instance()->getAllActivePlugins( DATA_PLOT );
  
      for( int i = 0; i < list.count(); i++ ){
     //     if( list[i] &&  ( list[i]->type() != FRAME_WORK ) ){
    //          ret_List.append( list[i]->cretate_plugin_object( list[i]->type() , parent ) );//DELL ME
          }
  
      return ret_List;
}

