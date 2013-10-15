
#include "qt/QFrameWork.h"
#include "qt/QCreator.h"
#include <QObject>


#include "qt/QPluginList.h"
QFrameWork::QFrameWork(QCreator * creator, QWidget * parent):QWidget(parent),CFrameWork(creator){
  DEBUG << "Create QFrameWork";
  setAttribute(Qt::WA_DeleteOnClose, true);
}

QFrameWork::~QFrameWork() {
  DEBUG << "Destroy QFrameWork";
  emit fwDestroy();
}

//bool QFrameWork::Create() {
//  if( m_creator )
//    return m_creator->Create( this );
//  else
//    return true;
//}


