#include "QFraMeasurementContext.h"
#include"QFraMeasureCommand.h"
#include "qt/QCommandExecutor.h"
#include "qt/QPacketCollector.h"
#include "qt/QPortIO.h"
#include "qt/QPacketCollector.h"
#include "QFraMeasureCommand.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFraMeasurementContext::QFraMeasurementContext(QObject *parent) :
    QObject(parent)
{
    m_status = E_IDLE;
}

QFraMeasurementContext::FraMeasureStatus QFraMeasurementContext::getStatus(){
    return m_status;
}

void QFraMeasurementContext::setCommandExecutor( QCommandExecutor* Executor ){
    m_Executor = Executor;
}

void QFraMeasurementContext::setPort( QPortIO* port ){
    m_port = port;
}

void QFraMeasurementContext::setProtocolPackFactory( QProtocolPackFactory* factory ){
    m_packetFactory = factory;
}

void QFraMeasurementContext::setPacketCollector( QPacketCollector* packetCollector ){
    m_packetCollector = packetCollector;
}

void QFraMeasurementContext::setMesConfig( FraMeasurementConfig& cfg ) {
    m_Cfg = cfg;
}


QCommandExecutor* QFraMeasurementContext::getCommandExecutor(){
    return m_Executor;
}

QPortIO* QFraMeasurementContext::getPort(){
    return m_port;
}

QProtocolPackFactory* QFraMeasurementContext::getProtocolPackFactory(){
    return m_packetFactory;
}

QPacketCollector* QFraMeasurementContext::getPacketCollector(){
    return m_packetCollector;
}

FraMeasurementConfig& QFraMeasurementContext::getMesConfig(){
    return m_Cfg;
}





bool  QFraMeasurementContext::startMeasure(){

    bool ret = false;
    if( paramsAreGood() )
    {
        m_packetCollector->setPort( m_port);
        if( !connect( m_port, SIGNAL(readyReadSignal()),m_packetCollector,SLOT(receivedBytesSlot()),Qt::UniqueConnection ) ){
            CRITICAL << "Can't connect Port with Packet Collector";
        }
        else{
            m_Executor->continueExecution();
            QFraMeasureCommand* command = new QFraMeasureCommand( this,  NULL /*TODO: TBD*/);
            m_Executor->appendCommand( command );
            ret = true;
        }
    }
    return ret ;
}

bool QFraMeasurementContext::paramsAreGood(){
    bool ret = false;
    if( m_port && m_packetCollector && m_Executor && m_packetFactory ){
        if( configIsGood() ){
            ret = true;
        }
        else{
            CRITICAL << "Wrong measurement Configuration";
        }
    }
    else{
        CRITICAL << "Not good measurment context: "<<endl << "Port '" << m_port
                 << "', Packet Colector '" << "', Executor '" << m_Executor
                 << "', Factory '" << m_packetFactory << "'";
    }
    return ret;
}

bool QFraMeasurementContext::configIsGood(){
    bool ret = false;
    ret = true; //TODO: TBD
    return ret;
}
