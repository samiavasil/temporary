
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QPacketCollector.h"

QFrameWork::QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent) :QWidget( parent),CFrameWork( factory){
  QPacketCollector* colect = dynamic_cast<QPacketCollector*> (m_Colector);
  QPortIO* port = dynamic_cast<QPortIO*> (m_PortIO);
  if( port&&colect ){
      connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
  }
}

QFrameWork::~QFrameWork() {
  DEBUG("Destroy QFrameWork");
}

