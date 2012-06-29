#include "QFraFrameWork.h"

QFraFrameWork::QFraFrameWork(QWidget *parent):QFrameWork( parent ),ui(new Ui::QFrameWorkView)
{
   ui->setupUi(this);
}


QFraFrameWork::~QFraFrameWork(){
     delete ui;
}
