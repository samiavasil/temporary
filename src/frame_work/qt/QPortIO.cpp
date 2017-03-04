#include "qt/QPortIO.h"
//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QPortIO::QPortIO(QObject * parent) :QObject(parent){
    m_PioWidget = NULL;
    m_PortType = UNDEFINED_IO;
    DEBUG<<"Create QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this;
}

QPortIO::portIo_type QPortIO::type() {
  return m_PortType;
}

QPortIO::~QPortIO()
{
    DEBUG<<"Destroy QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this;
    if( m_PioWidget )
    {
        delete m_PioWidget;
        m_PioWidget = NULL;
    }
    else
    {
        DEBUG<<" No m_PioWidget QPortIO type[" << m_PortType <<"] ptr = "<<(void*)this ;
    }
}
