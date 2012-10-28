#include "QFraFrameWork.h"
#include "qtestcommand.h"
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
}


QFraFrameWork::~QFraFrameWork(){
    DEBUG("Destroy QFraFrameWork");
    delete ui;
}
void QFraFrameWork::closeEvent ( QCloseEvent * event ){
    event = event;
    deleteLater();
}
