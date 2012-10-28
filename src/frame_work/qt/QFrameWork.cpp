
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QPacketCollector.h"

QFrameWork::QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent) :QWidget( parent),CFrameWork( factory){
    if( m_PortIO && m_Colector ){
        QPortIOSimulator* port            = dynamic_cast<QPortIOSimulator*> (m_PortIO);
        QPacketCollector* colect = dynamic_cast<QPacketCollector*> (m_Colector);
        connect( port, SIGNAL(readyReadBytesSignal()),colect,SLOT(receivedBytesSlot()) );
    }
  
    if( m_Executor ){
        /*QCommand* comm = new QCommand(this);
        m_Executor->appendCommand(comm);     
        TODO FIX ME
        sleep(1);
        m_Executor->pauseExecution(false);   */
    }
}

QFrameWork::~QFrameWork() {
  DEBUG("Destroy QFrameWork");
}

