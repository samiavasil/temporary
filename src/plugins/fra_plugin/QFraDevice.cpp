#include "QFraDevice.h"
#include "ui_QFraDevice.h"
#include "QPortsIoView.h"
#include "qt/QPortIO.h"
#include "qt/QPacketCollector.h"
#include "qt/QProtocolDb.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolLoader.h"
#include "qtestcommand.h"


//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFraDevice::QFraDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFraDevice)
{
    ui->setupUi(this);
    m_PIOList = new QPortsIoView( this );
    ui->PortIoConfig->addWidget(m_PIOList);
    QObject::connect(ui->StartButton, SIGNAL(clicked(bool)) , this, SLOT(onStartButtonclicked(bool)));


    m_packetFactory    = new QProtocolPackFactory( this );
    m_packetFactory->attachProtocolDb( new QProtocolDb() );
    m_packetFactory->attachProtocol( new QProtocolLoader() );
    m_packetCollector  = new QPacketCollector( NULL, m_packetFactory, this );

    QObject::connect( this,SIGNAL(destroyed()),m_Executor,SLOT(finish()) ,Qt::DirectConnection );
    m_Executor = new QCommandExecutor( this );
    if( 0 != m_Executor ){
        if( NO_ERR != m_Executor->startExecution() ){
            CRITICAL << "Can't start Executor thread";
        }
    }

    setWindowTitle( tr("Fra Device") );
}

QFraDevice::~QFraDevice()
{
    delete ui;
}



void QFraDevice::onStartButtonclicked( bool clicked )
{
    QPortIO* port = NULL;
    port = m_PIOList->getCurentIO();
    if( port )
    {
        m_packetCollector->setPort( port );
        if( port&&m_packetCollector ){
            connect( port, SIGNAL(readyReadSignal()),m_packetCollector,SLOT(receivedBytesSlot()),Qt::UniqueConnection );
        }


        m_Executor->continueExecution();

        QtestCommand* comm =NULL;
        for( int i=0; i<10; i++ )
        {
            comm = new QtestCommand( m_packetCollector, m_packetFactory, m_Executor);

            m_Executor->appendCommand(comm);
        }
        // sleep(1);//m_Executor->appendCommand(comm);

        /*TODO DELL ME
         sleep(1);*/
        //m_Executor->continueExecution();
        //  m_Executor->startExecution(true);
        //DELL ME set to false to run commands

    }

    DEBUG <<   tr("QFraFrameWork[%1]").arg(random());

}
