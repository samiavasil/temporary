#include "qt/QFrameWork.h"
#include "qt/QCreator.h"
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFrameWork::QFrameWork(QCreator * creator, QObject * parent):QObject(parent),CFrameWork(creator){
  DEBUG << "Create QFrameWork";
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


