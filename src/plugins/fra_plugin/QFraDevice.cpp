#include "QFraDevice.h"
#include "ui_QFraDevice.h"
#include "QPortsIoView.h"
#include "qt/QPortIO.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFraDevice::QFraDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFraDevice)
{
    ui->setupUi(this);
    m_PIOList = new QPortsIoView( this );
    ui->PortIoConfig->addWidget(m_PIOList);
    QObject::connect(ui->StartButton, SIGNAL(clicked(bool)) , this, SLOT(on_StartButton_clicked(bool)));
    setWindowTitle( tr("Fra Device") );
}

QFraDevice::~QFraDevice()
{
    delete ui;
}

#include "qt/QPacketCollector.h"
#include "qt/QProtocolDb.h"
#include "qt/QProtocolPackFactory.h"
#include "qt/QCommandExecutor.h"
#include "qt/QProtocolLoader.h"
#include "qtestcommand.h"

void QFraDevice::on_StartButton_clicked( bool clicked )
{
    QPortIO* port = NULL;
    port = m_PIOList->getCurentIO();
    if( port )
    {
        //TODO Sloji g wsichjki tia obekti da imat parent Qobject (primerno m_qfW) za da moje da se trie lesno
        //TODO All object  should be created from Factory

        QProtocolPackFactory* packetFactory    = new QProtocolPackFactory( port );
        packetFactory->attachProtocolDb( new QProtocolDb() );
        packetFactory->attachProtocol( new QProtocolLoader() );
        QPacketCollector*     colect  = new QPacketCollector( port, packetFactory, port );
        if( port&&colect ){
            connect( port, SIGNAL(readyReadSignal()),colect,SLOT(receivedBytesSlot()) );
        }
        //port->showPortConfiguration( NULL );

        QCommandExecutor* pExecutor = new QCommandExecutor( port );

        if( 0 != pExecutor ){
            if( NO_ERR != pExecutor->startExecution( true ) ){
                CRITICAL << "Can't start Executor thread";
            }
        }
        QObject::connect( this,SIGNAL(destroyed()),pExecutor,SLOT(finish()) ,Qt::DirectConnection );
        QtestCommand* comm =NULL;
        for(int i=0;i<1;i++)
        {
            comm = new QtestCommand( colect, packetFactory, pExecutor);

            pExecutor->appendCommand(comm);
        }
        // sleep(1);//pExecutor->appendCommand(comm);
        pExecutor->pauseExecution(false);
        /*TODO DELL ME*/
        // sleep(1);
        //  pExecutor->startExecution(true);
        //DELL ME set to false to run commands

    }

    DEBUG <<   tr("QFraFrameWork[%1]").arg(random());

}
