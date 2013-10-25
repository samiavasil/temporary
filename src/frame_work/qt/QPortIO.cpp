
#include "qt/QPortIO.h"

QPortIO::QPortIO(QObject * parent) :QObject(parent){
    m_PioWidget = NULL;
}

QPortIO::~QPortIO()
{
    if( m_PioWidget )
    {
        m_PioWidget->deleteLater();
    }
}
