#include "QFraFrameWork.h"
#include <ui_qfra_frame_work_view.h>

QFraFrameWork::QFraFrameWork(QCreator * creator  , QWidget * parent ):
    QFrameWork( creator , parent ),ui(new Ui::QFraFrameWorkView)
{
    ui->setupUi(this);
}
QFraFrameWork::~QFraFrameWork(){

}

void QFraFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{
    ui->verticalLayout->addWidget(widget);
}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
     ui->PortIoConfig->addWidget(widget);
}
