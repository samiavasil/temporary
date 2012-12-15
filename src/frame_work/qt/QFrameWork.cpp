
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPortIOSimulator.h"
#include "qt/QSerialPortIO.h"
#include "qt/QPacketCollector.h"

QFrameWork::QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent) :QWidget( parent),CFrameWork( factory){

    QPacketCollector* colect = dynamic_cast<QPacketCollector*> (m_Colector);
    QPortIO* port = dynamic_cast<QPortIO*> (m_PortIO);
    if( port&&colect ){
        connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
    }
    if( m_PortIO && m_Colector ){

        switch( m_PortIO->type() ){
        case CPortIO::SIMULATOR_IO:{
            break;

        }
        case CPortIO::SERIALPORT_IO:{
            if( port&&colect ){
               /*DELL ME*/
               ((QSerialPortIO*) port)->open();
               ((QSerialPortIO*) port)->showPortConfiguration( NULL );
            }

            break;

        }
        }


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

