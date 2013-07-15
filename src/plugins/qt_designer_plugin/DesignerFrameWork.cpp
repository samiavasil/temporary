#include "DesignerFrameWork.h"
#include <QDebug>
#include <QGridLayout>

#include "base/CCreator.h"

DesignerFrameWork::DesignerFrameWork(QCreator * creator  , QWidget * parent ):
    QFrameWork( creator , parent )
{

    //setAttribute(Qt::WA_DeleteOnClose, true);
}

DesignerFrameWork::~DesignerFrameWork()
{
    //qDebug()<<"iooopiop"<<endl<<endl<<endl;
    m_creator->Free();
}

void DesignerFrameWork::AddWidgetToControlArrea ( QWidget* widget )
{
    if( NULL == this->layout() )
    {
        setLayout( new QGridLayout(this) );
    }
    if( widget )
    {
        layout()->addWidget( widget );
    }
}

void DesignerFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{

}
