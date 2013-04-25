
#include "qt/QFrameWork.h"
#include "qt/QCreator.h"
#include <QObject>


#include "qt/QPluginList.h"
QFrameWork::QFrameWork(QCreator * creator, QWidget * parent):QWidget(parent),CFrameWork(creator){
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


