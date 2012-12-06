#include "qt/QSerialPortIO.h"
#include "ui_serial_port.h"
#include <QDialog>
#include "qextserialenumerator.h"


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
    connect( ui->portCombo,        SIGNAL(activated(QString)), this, SLOT( setPortName(const QString )) );
    connect( ui->queryModeCombo,   SIGNAL(activated(int)),     this, SLOT( setQueryMode(int) )    );
    connect( ui->baudRateCombo,    SIGNAL(activated(QString)), this, SLOT( setBaudRate(BaudRateType))   );
    connect( ui->parityCombo,      SIGNAL(activated(int)),     this, SLOT( setParity(ParityType) )      );
    connect( ui->stopBitsCombo,    SIGNAL(activated(int)),     this, SLOT( setStopBits(StopBitsType) )  );
    connect( ui->flowControlCombo, SIGNAL(activated(QString)), this, SLOT( setFlowControl(FlowType))    );
    connect( ui->timeoutSpin,      SIGNAL(activated(int)),     this, SLOT( setTimeout(long) )           );

}


/*
void QSerialPortIO::setPortName( const QString portName ){

}
*/
void QSerialPortIO::setQueryMode( int act ){
    setQueryMode( (QueryMode)ui->queryModeCombo->itemData( act ).toInt() );
}

void QSerialPortIO::setBaudRate( int rate ){
    setBaudRate((BaudRateType)ui->baudRateCombo->itemData( rate ).toInt() );
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


