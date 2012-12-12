#include "qt/QSerialPortIO.h"
#include "ui_serial_port.h"
#include <QDialog>
#include "qextserialenumerator.h"

#define GET_NAME(x) #x

typedef struct {
     const char*  name;
     BaudRateType value;
} baud_rates_t;

typedef struct {
    const char*  name;
    DataBitsType value;
} dataBits_t;

typedef struct {
    const char* name;
    ParityType  value;
} parity_t;

typedef struct {
    const char*  name;
    StopBitsType value;
} stopBits_t;

typedef struct {
    const char*  name;
    FlowType     value;
} flowType_t;

typedef struct {
    const char*  name;
    QextSerialPort::QueryMode value;
} queryMode_t;


const baud_rates_t supportedBaudRateType[]=
{
#if defined(Q_OS_UNIX) || defined(qdoc)
    {GET_NAME(BAUD50),   BAUD50},
    {GET_NAME(BAUD75),   BAUD75},
    {GET_NAME(BAUD134),  BAUD134},
    {GET_NAME(BAUD150),  BAUD150},
    {GET_NAME(BAUD200),  BAUD200},
    {GET_NAME(BAUD1800), BAUD1800},
#  if defined(B76800) || defined(qdoc)
    {GET_NAME(BAUD76800), BAUD76800},
#  endif
#  if (defined(B230400) && defined(B4000000)) || defined(qdoc)
    {GET_NAME(BAUD230400), BAUD230400},
    {GET_NAME(BAUD460800), BAUD460800},
    {GET_NAME(BAUD500000), BAUD500000},
    {GET_NAME(BAUD576000), BAUD576000},
    {GET_NAME(BAUD921600), BAUD921600},
    {GET_NAME(BAUD1000000),BAUD1000000},
    {GET_NAME(BAUD1152000),BAUD1152000},
    {GET_NAME(BAUD1500000),BAUD1500000},
    {GET_NAME(BAUD2000000),BAUD2000000},
    {GET_NAME(BAUD2500000),BAUD2500000},
    {GET_NAME(BAUD3000000),BAUD3000000},
    {GET_NAME(BAUD3500000),BAUD3500000},
    {GET_NAME(BAUD4000000),BAUD4000000},
#  endif
#endif //Q_OS_UNIX
#if defined(Q_OS_WIN) || defined(qdoc)
    {GET_NAME(BAUD14400) , BAUD14400 },
    {GET_NAME(BAUD56000) , BAUD56000 },
    {GET_NAME(BAUD128000), BAUD128000},
    {GET_NAME(BAUD256000), BAUD256000},
#endif  //Q_OS_WIN
    {GET_NAME(BAUD110)    , BAUD110 },
    {GET_NAME(BAUD300)    , BAUD300 },
    {GET_NAME(BAUD600)    , BAUD600 },
    {GET_NAME(BAUD1200)   , BAUD1200 },
    {GET_NAME(BAUD2400)   , BAUD2400 },
    {GET_NAME(BAUD4800)   , BAUD4800 },
    {GET_NAME(BAUD9600)   , BAUD9600 },
    {GET_NAME(BAUD19200)  , BAUD19200 },
    {GET_NAME(BAUD38400)  , BAUD38400 },
    {GET_NAME(BAUD57600)  , BAUD57600 },
    {GET_NAME(BAUD115200) , BAUD115200 },
};

dataBits_t dataBitsArrea[] = {
    {GET_NAME(DATA_5)    , DATA_5 },
    {GET_NAME(DATA_6)    , DATA_6 },
    {GET_NAME(DATA_7)    , DATA_7 },
    {GET_NAME(DATA_8)    , DATA_8 },
};

stopBits_t stopBitsArrea[] = {
    {GET_NAME(STOP_1)    , STOP_1 },
#if defined(Q_OS_WIN) || defined(qdoc)
    {GET_NAME(STOP_1_5)  , STOP_1_5 },
#endif
    {GET_NAME(STOP_2)    , STOP_2 },
};

flowType_t flowTypeArrea[] = {
    {GET_NAME(FLOW_OFF)     , FLOW_OFF },
    {GET_NAME(FLOW_HARDWARE), FLOW_HARDWARE },
    {GET_NAME(FLOW_XONXOFF) , FLOW_XONXOFF },
};

parity_t parityArrea[]=
{
    {GET_NAME(PAR_NONE)     , PAR_NONE },
    {GET_NAME(PAR_ODD)      , PAR_ODD  },
    {GET_NAME(PAR_EVEN)     , PAR_EVEN },
#if defined(Q_OS_WIN) || defined(qdoc)
    {GET_NAME(PAR_MARK)     , PAR_MARK },
#endif
    {GET_NAME(PAR_SPACE)     , PAR_SPACE },
};

queryMode_t queryModeArrea[]=
{
    { "Polling"     , QextSerialPort::Polling     },
    { "EventDriven" , QextSerialPort::EventDriven },
};


QSerialPortIO::QSerialPortIO(QextSerialPort::QueryMode mode):m_Serial( mode ),ui(new Ui::SerialPortConfig) {
    DEBUG("Create QSerialPortIO");
    m_PortType = SERIALPORT_IO;
    connect( &m_Serial,SIGNAL(readyRead()),this,SLOT(dataReady()) );
}

QSerialPortIO::~QSerialPortIO() {
    DEBUG("Destroy QPortIO");

}

void QSerialPortIO::dataReady(){
    emit readyReadSignal();
}
//#define stringify( name ) # name
void QSerialPortIO::initUi(){
    int i;
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach (QextPortInfo info, ports) {
        qDebug() << "port name:"       << info.portName;
        qDebug() << "friendly name:"   << info.friendName;
        qDebug() << "physical name:"   << info.physName;
        qDebug() << "enumerator name:" << info.enumName;
        qDebug() << "vendor ID:"       << info.vendorID;
        qDebug() << "product ID:"      << info.productID;
        ui->portCombo->addItem( info.physName );
        //ui->queryModeCombo->setItemData();
    }
    for( i = 0; i < (int)(sizeof(supportedBaudRateType)/sizeof(supportedBaudRateType[0])) ;i++ ){
        ui->baudRateCombo->addItem( supportedBaudRateType[i].name );
        ui->baudRateCombo->setItemData( i,  supportedBaudRateType[i].value );
    }

    for( i = 0; i < (int)(sizeof(dataBitsArrea)/sizeof(dataBitsArrea[0])) ;i++ ){
        ui->dataBitsCombo->addItem( dataBitsArrea[i].name );
        ui->dataBitsCombo->setItemData( i,  dataBitsArrea[i].value );
    }

    for( i=0; i < (int)(sizeof(stopBitsArrea)/sizeof(stopBitsArrea[0])) ;i++ ){
        ui->stopBitsCombo->addItem( stopBitsArrea[i].name );
        ui->stopBitsCombo->setItemData(  i, stopBitsArrea[i].value );
    }

    for( i=0; i < (int)(sizeof(flowTypeArrea)/sizeof(flowTypeArrea[0])) ;i++ ){
        ui->flowControlCombo->addItem( flowTypeArrea[i].name );
        ui->flowControlCombo->setItemData(  i, flowTypeArrea[i].value );
    }

    for( i=0; i < (int)(sizeof(parityArrea)/sizeof(parityArrea[0])) ;i++ ){
        ui->parityCombo->addItem( parityArrea[i].name );
        ui->parityCombo->setItemData( i, parityArrea[i].value );
    }

    for( i=0; i < (int)(sizeof(queryModeArrea)/sizeof(queryModeArrea[0])) ;i++ ){
        ui->queryModeCombo->addItem( queryModeArrea[i].name );
        ui->queryModeCombo->setItemData( i, queryModeArrea[i].value );
    }

    connect( ui->portCombo,        SIGNAL(activated(QString)), this, SLOT( setPortName(const QString )) );
    connect( ui->queryModeCombo,   SIGNAL(activated(int)),     this, SLOT( setQueryMode(int) )    );

    connect( ui->baudRateCombo,    SIGNAL(activated(int)), this, SLOT( setBaudRate(int))   );
    connect( ui->parityCombo,      SIGNAL(activated(int)),     this, SLOT( setParity(ParityType) )      );
    connect( ui->stopBitsCombo,    SIGNAL(activated(int)),     this, SLOT( setStopBits(StopBitsType) )  );
    connect( ui->flowControlCombo, SIGNAL(activated(QString)), this, SLOT( setFlowControl(FlowType))    );
    connect( ui->timeoutSpin,      SIGNAL(activated(int)),     this, SLOT( setTimeout(long) )           );
  /**/
}


/*
void QSerialPortIO::setPortName( const QString portName ){

}
*/
void QSerialPortIO::setQueryMode( int act ){
    QueryMode mode = (QueryMode)ui->queryModeCombo->itemData( act ).toULongLong();
    qDebug()<<mode;
    QextSerialPort::setQueryMode( mode );
}

void QSerialPortIO::setBaudRate( int rate ){
    QextSerialPort::setBaudRate((BaudRateType)ui->baudRateCombo->itemData( rate ).toInt() );
}

void QSerialPortIO::setParity(ParityType){

}

void QSerialPortIO::setStopBits(StopBitsType){

}

void QSerialPortIO::setFlowControl(FlowType){

}

void QSerialPortIO::setTimeout(long){

}









void QSerialPortIO::showPortConfiguration( QWidget* parent ){
    if( parent ){
       ui->setupUi( parent );
       initUi();
    }
    else{
        QDialog dlg;
        ui->setupUi(&dlg);
        initUi();
        dlg.exec();
    }
}


