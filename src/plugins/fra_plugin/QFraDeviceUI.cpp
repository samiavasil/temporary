#include "QFraDeviceUI.h"
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


struct combo_item{
   const char* name;
   double value;
};


/*
TODO: This can be moved on some configuration type file and read from there.
Not constantly defined as in this keys.
*/
static const struct combo_item freqItems[] = {
    { "Hz" , 1.0 },
    { "KHz", 1000.0 },
    { "MHz", 1000000.0 },
};

static const struct combo_item currentItems[] = {
    { "uA", 1e-6 },
    { "mA", 1e-3 },
    { "A" , 1.0  },
};

static void initCombo( QComboBox * combo,const combo_item* items, int num )
{
    if( combo && items)
    {
        int i;
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/icons/radiobutton_on.png"), QSize(), QIcon::Normal, QIcon::Off);

        combo->clear();
        for( i = 0; i < num; i++ ){
            combo->addItem( icon, QString(QString::fromUtf8(items[i].name)) );
            combo->setItemData( i, QVariant(items[i].value));
        }
    }
}

QFraDeviceUI::QFraDeviceUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFraDevice)
{

    ui->setupUi(this);



    initCombo( ui->StartFreqComboBox, freqItems   , sizeof( freqItems )/sizeof( freqItems[0] ) );
    initCombo( ui->StopFreqComboBox , freqItems   , sizeof( freqItems )/sizeof( freqItems[0] ) );
    initCombo( ui->CurrentComboBox  , currentItems, sizeof( currentItems )/sizeof( currentItems[0] ) );

    m_PIOList = new QPortsIoView( this );
    ui->PortIoConfig->addWidget(m_PIOList);
    QObject::connect(ui->StartButton, SIGNAL(clicked(bool)) , this, SLOT(onStartButtonclicked(bool)));

    QProtocolLoader Loader;
    QProtocolDb* pDb = new QProtocolDb();
    pDb->loadProtocolDefinition(Loader);
/*
u8 data[2];
data[0]=0x1;
data[1]=0x34;
pDb->setMessage(AIN1_ENBLE,data);
data[0]=0x1;
data[1]=0xff;
pDb->setMessage(AIN2_ENBLE,data);
data[0]=0xff;
data[1]=0xbc;
pDb->setMessage(AIN1_GAIN,data);
data[0]=0xff;
data[1]=0x1f;
pDb->setMessage(AIN2_GAIN,data);
*/
    m_packetFactory    = new QProtocolPackFactory( pDb, this );
    m_packetCollector  = new QPacketCollector( NULL, m_packetFactory, this );
    m_Executor = new QCommandExecutor( this );
    if( 0 != m_Executor ){
        QObject::connect( this,SIGNAL(destroyed()),m_Executor,SLOT(finish()) ,Qt::DirectConnection );
        if( NO_ERR != m_Executor->startExecution() ){
            CRITICAL << "Can't start Executor thread";
        }
    }

    setWindowTitle( tr("Fra Device") );
}

QFraDeviceUI::~QFraDeviceUI()
{
    delete ui;
}




#define getComboScalleFactor( combo )   combo?( combo->itemData( combo->currentIndex() ).toDouble() ):(0.0)

int QFraDeviceUI::getMeasurementParams( FraMeasurementConfig &params )
{
    double val;
    val = getComboScalleFactor( ui->StartFreqComboBox );
    val = val*ui->StartFreqSpinBox->value();
    params.SetStartFrequencyUi( val );

    val = getComboScalleFactor( ui->StopFreqComboBox );
    val = val*ui->StopFreqSpinBox->value();
    params.SetStopFrequencyUi( val );

    val = getComboScalleFactor( ui->CurrentComboBox );
    val = val*ui->CurrentSpinBox->value();
    params.SetOutputCurrentUi( val );

    params.SetNumberOfPoints( ui->NumPointsSpinBox->value() );
    params.SetDelayMsec( ui->TimeDelaySpinBox->value() );
    params.SetScaleType( ui->LinearButton->isChecked() ? FraMeasurementConfig::E_LINEAR: FraMeasurementConfig::E_LOGARITMIC );

    params.DumpConfig();
    return 0;
}


#include<QMessageBox>
#include"QFraMeasurementContext.h"
#include"QFraMeasureCommand.h"

void QFraDeviceUI::onStartButtonclicked( bool clicked )
{
    FraMeasurementConfig params;
    QPortIO* port = NULL;

    if( QFraMeasurementContext::E_IDLE != mes_ctx.getStatus() ){
        QMessageBox msgBox;
        msgBox.setText(tr("Measurement is in progress. Stop it or wait for finish!!"));
        msgBox.exec();
        return;
    }
    if( !getMeasurementParams( params ) )
    {
        mes_ctx.setMesConfig( params );
        mes_ctx.setCommandExecutor( m_Executor );
        mes_ctx.setPacketCollector( m_packetCollector );
        mes_ctx.setPort( m_PIOList->getCurentIO() );
        mes_ctx.setProtocolPackFactory( m_packetFactory );
        mes_ctx.startMeasure();

return; //TODO: DELL ALL

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
        }
    }
    DEBUG <<   tr("QFraFrameWork[%1]").arg(random());

}
