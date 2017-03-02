#include "DesignerFrameWork.h"
#include "DesignerCreator.h"
#include <QDebug>
#include <QGridLayout>

DesignerFrameWork::DesignerFrameWork(QCreator * creator  , QObject *parent ):
    QFrameWork( creator , parent )
{

   //new QGridLayout(m_FwWin);
}

DesignerFrameWork::~DesignerFrameWork()
{
    //qDebug()<<"iooopiop"<<endl<<endl<<endl;
    if( m_creator )//TODO: Check this
    {
        DesignerCreator* creator = dynamic_cast<DesignerCreator*>(m_creator);
        if( creator )
        {
           m_creator->Free();
        }
    }

}

void DesignerFrameWork::AddWidgetToControlArrea ( QWidget* widget )
{
    m_FwWin->layout()->addWidget( widget );

}

void DesignerFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{

}
