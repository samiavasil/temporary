#include "QFraFrameWork.h"

QFraFrameWork::QFraFrameWork(QFrameWorkElementsFactory *factory, QWidget *parent):
    QFrameWork( factory, parent ),ui(new Ui::QFrameWorkView)
{
   ui->setupUi(this);
}


QFraFrameWork::~QFraFrameWork(){
     delete ui;
}
