#include "QFraFrameWork.h"

QFraFrameWork::QFraFrameWork(QFrameWorkElementsFactory *factory, QWidget *parent):
    QFrameWork( factory, parent ),ui(new Ui::QFraFrameWorkView)
{
   qDebug("Create QFraFrameWork");
   ui->setupUi(this);
   //setCentralWidget(ui->mdiArea);
}


QFraFrameWork::~QFraFrameWork(){
    qDebug("Destroy QFraFrameWork");
    delete ui;
}
