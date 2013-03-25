#include "QFraFrameWork.h"
#include "qtestcommand.h"

#include "qt/QSerialPortIO.h"
QFraFrameWork::QFraFrameWork(QFrameWorkElementsFactory *factory, QWidget *parent):
    QFrameWork( factory, parent ),ui(new Ui::QFraFrameWorkView)
{
   DEBUG("Create QFraFrameWork");
   ui->setupUi(this);
   QtestCommand* comm = new QtestCommand(this);
   m_Executor->appendCommand(comm);
   /*TODO FIX ME*/
   sleep(1);
   m_Executor->pauseExecution(false);
   //setCentralWidget(ui->mdiArea);
   if( m_PortIO )//DELL ME
   {
        ((QSerialPortIO*) m_PortIO)->showPortConfiguration( ui->Seriala );
       ((QSerialPortIO*) m_PortIO)->showPortConfiguration( NULL );
   }
   setAttribute(Qt::WA_DeleteOnClose, true);
}

QFraFrameWork::QFraFrameWork( QCreator* creator , QWidget * parent ):QFrameWork( creator, parent ),ui(new Ui::QFraFrameWorkView)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
}

QFraFrameWork::~QFraFrameWork(){
    DEBUG("Destroy QFraFrameWork");
    delete ui;
}

