#include "DesignerFrameWork.h"
#include <QDebug>
#include <QGridLayout>

#include "base/CCreator.h"

DesignerFrameWork::DesignerFrameWork(QCreator * creator  , QObject *parent ):
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
    m_FwWin->setLayout( new QGridLayout( m_FwWin ) );

    if( widget )
    {
        m_FwWin->layout()->addWidget( widget );
    }
}

void DesignerFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{

}
