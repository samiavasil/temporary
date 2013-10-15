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
    list.append(widget);
}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
     ui->PortIoConfig->addWidget(widget);
}

void QFraFrameWork::on_StartButton_clicked()
{
    static bool b;
    b=!b;
    for( int i = 0; i< list.count(); i++ )
     list[i]->setProperty( "TestPropety", b );
}
