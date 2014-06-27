#include "qt/QSerialPortIO.h"
#include <QDialog>
#include <qtserial/qextserialenumerator.h>
#include <QObject>
#include <QWidget>
#include "ui_serial_port.h"


//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"


#define GET_NAME(x) #x
#define EXPAND_TO_NAME_AND_ENUM(x) { GET_NAME(x),x }

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
    EXPAND_TO_NAME_AND_ENUM(BAUD50),
    EXPAND_TO_NAME_AND_ENUM(BAUD75),
    EXPAND_TO_NAME_AND_ENUM(BAUD134),
    EXPAND_TO_NAME_AND_ENUM(BAUD150),
    EXPAND_TO_NAME_AND_ENUM(BAUD200),
    EXPAND_TO_NAME_AND_ENUM(BAUD1800),
    #  if defined(B76800) || defined(qdoc)
    EXPAND_TO_NAME_AND_ENUM(BAUD76800), BAUD76800},
#  endif
#  if (defined(B230400) && defined(B4000000)) || defined(qdoc)
EXPAND_TO_NAME_AND_ENUM(BAUD230400),
EXPAND_TO_NAME_AND_ENUM(BAUD460800),
EXPAND_TO_NAME_AND_ENUM(BAUD500000),
EXPAND_TO_NAME_AND_ENUM(BAUD576000),
EXPAND_TO_NAME_AND_ENUM(BAUD921600),
EXPAND_TO_NAME_AND_ENUM(BAUD1000000),
EXPAND_TO_NAME_AND_ENUM(BAUD1152000),
EXPAND_TO_NAME_AND_ENUM(BAUD1500000),
EXPAND_TO_NAME_AND_ENUM(BAUD2000000),
EXPAND_TO_NAME_AND_ENUM(BAUD2500000),
EXPAND_TO_NAME_AND_ENUM(BAUD3000000),
EXPAND_TO_NAME_AND_ENUM(BAUD3500000),
EXPAND_TO_NAME_AND_ENUM(BAUD4000000),
#  endif
#endif //Q_OS_UNIX
#if defined(Q_OS_WIN) || defined(qdoc)
EXPAND_TO_NAME_AND_ENUM(BAUD14400) ,
EXPAND_TO_NAME_AND_ENUM(BAUD56000) ,
EXPAND_TO_NAME_AND_ENUM(BAUD128000),
EXPAND_TO_NAME_AND_ENUM(BAUD256000),
#endif  //Q_OS_WIN
EXPAND_TO_NAME_AND_ENUM(BAUD110)    ,
EXPAND_TO_NAME_AND_ENUM(BAUD300)    ,
EXPAND_TO_NAME_AND_ENUM(BAUD600)    ,
EXPAND_TO_NAME_AND_ENUM(BAUD1200)   ,
EXPAND_TO_NAME_AND_ENUM(BAUD2400)   ,
EXPAND_TO_NAME_AND_ENUM(BAUD4800)   ,
EXPAND_TO_NAME_AND_ENUM(BAUD9600)   ,
EXPAND_TO_NAME_AND_ENUM(BAUD19200)  ,
EXPAND_TO_NAME_AND_ENUM(BAUD38400)  ,
EXPAND_TO_NAME_AND_ENUM(BAUD57600)  ,
EXPAND_TO_NAME_AND_ENUM(BAUD115200) ,
};

dataBits_t dataBitsArrea[] = {
    EXPAND_TO_NAME_AND_ENUM(DATA_5)    ,
    EXPAND_TO_NAME_AND_ENUM(DATA_6)    ,
    EXPAND_TO_NAME_AND_ENUM(DATA_7)    ,
    EXPAND_TO_NAME_AND_ENUM(DATA_8)    ,
};

stopBits_t stopBitsArrea[] = {
    EXPAND_TO_NAME_AND_ENUM(STOP_1)    ,
    #if defined(Q_OS_WIN) || defined(qdoc)
    EXPAND_TO_NAME_AND_ENUM(STOP_1_5)  ,
    #endif
    EXPAND_TO_NAME_AND_ENUM(STOP_2)    ,
};

flowType_t flowTypeArrea[] = {
    EXPAND_TO_NAME_AND_ENUM(FLOW_OFF)     ,
    EXPAND_TO_NAME_AND_ENUM(FLOW_HARDWARE),
    EXPAND_TO_NAME_AND_ENUM(FLOW_XONXOFF) ,
};

parity_t parityArrea[]=
{
    EXPAND_TO_NAME_AND_ENUM(PAR_NONE)     ,
    EXPAND_TO_NAME_AND_ENUM(PAR_ODD)      ,
    EXPAND_TO_NAME_AND_ENUM(PAR_EVEN)     ,
    #if defined(Q_OS_WIN) || defined(qdoc)
    EXPAND_TO_NAME_AND_ENUM(PAR_MARK)     ,
    #endif
    EXPAND_TO_NAME_AND_ENUM(PAR_SPACE)     ,
};

queryMode_t queryModeArrea[]=
{
    { "Polling"     , QextSerialPort::Polling     },
    { "EventDriven" , QextSerialPort::EventDriven },
};

QSerialPortIO::QSerialPortIO(QObject * parent, const QextSerialPort::QueryMode & mode) :QPortIO(parent),ui(new Ui::SerialPortConfig),m_Serial( mode ){
    DEBUG << "Create QSerialPortIO";
    m_PortType = SERIALPORT_IO;
    connect( &m_Serial,SIGNAL(readyRead()),this,SLOT(dataReady()) );
}

QSerialPortIO::~QSerialPortIO() {
    DEBUG << "Destroy QPortIO";
    delete ui;
}

void QSerialPortIO::showPortConfiguration(QWidget * parent) {
    if( 0 != m_PioWidget )
    {
        //TODO ???????
        m_PioWidget->setVisible( true );
        return;
    }
    if( parent ){
        m_PioWidget = new  QWidget( parent );
        parent->setLayout( new QGridLayout(parent) );
        parent->layout()->addWidget( m_PioWidget );
        ui->setupUi( m_PioWidget );
        initUi();
    }
    else{
        QDialog* dlg = new QDialog();
        m_PioWidget = dlg;
        ui->setupUi(dlg);
        initUi();
        dlg->exec();
    }
}

void QSerialPortIO::initUi() {
    int i;
    bool cmp = false;
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    foreach (QextPortInfo info, ports) {
        DEBUG << "port name:"       << info.portName;
        DEBUG << "friendly name:"   << info.friendName;
        DEBUG << "physical name:"   << info.physName;
        DEBUG << "enumerator name:" << info.enumName;
        DEBUG << "vendor ID:"       << info.vendorID;
        DEBUG << "product ID:"      << info.productID;
        ui->portCombo->addItem( info.physName );
        if( !m_Serial.portName().compare( info.physName ) ){
            cmp = true;
            ui->portCombo->setCurrentIndex( ui->portCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->portCombo->count() ){
            ui->portCombo->setCurrentIndex( 0 );
            m_Serial.setPortName( ports[0].physName );
        }
    }


    cmp = false;
    for( i = 0; i < (int)(sizeof(supportedBaudRateType)/sizeof(supportedBaudRateType[0])) ;i++ ){
        ui->baudRateCombo->addItem( supportedBaudRateType[i].name );
        ui->baudRateCombo->setItemData( i,  supportedBaudRateType[i].value );
        if( m_Serial.baudRate() == supportedBaudRateType[i].value ){
            cmp = true;
            DEBUG << "Baud Rate: "<< m_Serial.baudRate();
            ui->baudRateCombo->setCurrentIndex( ui->baudRateCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->baudRateCombo->count() ){
            ui->baudRateCombo->setCurrentIndex( 0 );
            m_Serial.setBaudRate( supportedBaudRateType[0].value );
        }
    }

    cmp = false;
    for( i = 0; i < (int)(sizeof(dataBitsArrea)/sizeof(dataBitsArrea[0])) ;i++ ){
        ui->dataBitsCombo->addItem( dataBitsArrea[i].name );
        ui->dataBitsCombo->setItemData( i,  dataBitsArrea[i].value );
        if( m_Serial.dataBits() == dataBitsArrea[i].value ){
            cmp = true;
            DEBUG << "dataBits: "<< m_Serial.dataBits();
            ui->dataBitsCombo->setCurrentIndex( ui->dataBitsCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->dataBitsCombo->count() ){
            ui->dataBitsCombo->setCurrentIndex( 0 );
            m_Serial.setDataBits( dataBitsArrea[0].value );
        }
    }

    cmp = false;
    for( i=0; i < (int)(sizeof(stopBitsArrea)/sizeof(stopBitsArrea[0])) ;i++ ){
        ui->stopBitsCombo->addItem( stopBitsArrea[i].name );
        ui->stopBitsCombo->setItemData(  i, stopBitsArrea[i].value );
        if( m_Serial.stopBits() == stopBitsArrea[i].value ){
            cmp = true;
            DEBUG << "dataBits: "<< m_Serial.stopBits();
            ui->stopBitsCombo->setCurrentIndex( ui->stopBitsCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->stopBitsCombo->count() ){
            ui->stopBitsCombo->setCurrentIndex( 0 );
            m_Serial.setStopBits( stopBitsArrea[0].value );
        }
    }

    cmp = false;
    for( i=0; i < (int)(sizeof(flowTypeArrea)/sizeof(flowTypeArrea[0])) ;i++ ){
        ui->flowControlCombo->addItem( flowTypeArrea[i].name );
        ui->flowControlCombo->setItemData(  i, flowTypeArrea[i].value );
        if( m_Serial.flowControl() == flowTypeArrea[i].value ){
            cmp = true;
            DEBUG << "FlowControl: "<< m_Serial.flowControl();
            ui->stopBitsCombo->setCurrentIndex( ui->stopBitsCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->flowControlCombo->count() ){
            ui->flowControlCombo->setCurrentIndex( 0 );
            m_Serial.setFlowControl( flowTypeArrea[0].value );
        }
    }

    cmp = false;
    for( i=0; i < (int)(sizeof(parityArrea)/sizeof(parityArrea[0])) ;i++ ){
        ui->parityCombo->addItem( parityArrea[i].name );
        ui->parityCombo->setItemData( i, parityArrea[i].value );
        if( m_Serial.parity() == parityArrea[i].value ){
            cmp = true;
            DEBUG << "parity: "<< m_Serial.parity();
            ui->stopBitsCombo->setCurrentIndex( ui->stopBitsCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->parityCombo->count() ){
            ui->parityCombo->setCurrentIndex( 0 );
            m_Serial.setParity( parityArrea[0].value );
        }
    }


    for( i=0; i < (int)(sizeof(queryModeArrea)/sizeof(queryModeArrea[0])) ;i++ ){
        ui->queryModeCombo->addItem( queryModeArrea[i].name );
        ui->queryModeCombo->setItemData( i, queryModeArrea[i].value );
        if( m_Serial.queryMode() == queryModeArrea[i].value ){
            cmp = true;
            DEBUG << "queryMode: "<< m_Serial.queryMode();
            ui->queryModeCombo->setCurrentIndex( ui->queryModeCombo->count() - 1 );
        }
    }
    if( !cmp ){
        if( ui->queryModeCombo->count() ){
            ui->queryModeCombo->setCurrentIndex( 0 );
            m_Serial.setQueryMode( queryModeArrea[0].value );
        }
    }

    connect( ui->portCombo,        SIGNAL(activated(QString)), this, SLOT( setPortName(const QString )));
    connect( ui->queryModeCombo,   SIGNAL(activated(int)),     this, SLOT( setQueryMode(int) ) );
    connect( ui->baudRateCombo,    SIGNAL(activated(int)),     this, SLOT( setBaudRate(int))   );
    connect( ui->parityCombo,      SIGNAL(activated(int)),     this, SLOT( setParity(int) )    );
    connect( ui->stopBitsCombo,    SIGNAL(activated(int)),     this, SLOT( setStopBits(int) )  );
    connect( ui->flowControlCombo, SIGNAL(activated(int)), this, SLOT( setFlowControl(int))    );
    connect( ui->timeoutSpin,      SIGNAL(valueChanged(int)),     this, SLOT( setTimeout(int) ));
}

void QSerialPortIO::dataReady() {
    emit readyReadSignal();
}

void QSerialPortIO::setPortName(const QString & portName) {
    m_Serial.setPortName( portName );
}

void QSerialPortIO::setQueryMode(int act) {
    QextSerialPort::QueryMode mode = (QextSerialPort::QueryMode)ui->queryModeCombo->itemData( act ).toULongLong();
    DEBUG <<mode;
    m_Serial.setQueryMode( mode );
}

void QSerialPortIO::setBaudRate(int rate) {
    m_Serial.setBaudRate( (BaudRateType)ui->baudRateCombo->itemData( rate ).toInt() );
}

void QSerialPortIO::setParity(int par) {
    m_Serial.setParity( (ParityType)ui->parityCombo->itemData( par ).toInt()  );
}

void QSerialPortIO::setStopBits(int stop) {
    m_Serial.setStopBits( (StopBitsType)ui->stopBitsCombo->itemData( stop ).toInt()  );
}

void QSerialPortIO::setFlowControl(int flow) {
    m_Serial.setFlowControl( (FlowType)ui->flowControlCombo->itemData( flow ).toInt()  );
}

void QSerialPortIO::setTimeout(int timeout_Ms) {
    m_Serial.setTimeout( timeout_Ms*1000 );
}

