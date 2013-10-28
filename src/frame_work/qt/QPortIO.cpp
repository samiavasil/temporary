
#include "qt/QPortIO.h"
#include<QDebug>
QPortIO::QPortIO(QObject * parent) :QObject(parent){
    m_PioWidget = NULL;
    qDebug()<<"Create QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this;
}

QPortIO::~QPortIO()
{
    qDebug()<<"Destroy QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this;
    if( m_PioWidget )
    {
        delete m_PioWidget;
        m_PioWidget = NULL;
    }
    else
    {
        qDebug()<<" No m_PioWidget QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this ;
    }
}
