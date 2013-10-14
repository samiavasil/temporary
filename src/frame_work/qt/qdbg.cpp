#include "base/global.h"
#include "qdbg.h"
#include<QDebug>
#include<QDynamicPropertyChangeEvent>
QDbg* m_Debug;
PropertyChangedFilter::PropertyChangedFilter(  QObject *parent ):QObject(parent)
{

}

bool PropertyChangedFilter::eventFilter(QObject *obj, QEvent *event)
{

    if ( event->type() == QEvent::DynamicPropertyChange ) {
        //emit dynamicPropertyChanged( static_cast<QDynamicPropertyChangeEvent*>(e)->propertyName() );
        QDynamicPropertyChangeEvent* pChEv =  static_cast<QDynamicPropertyChangeEvent*>(event);
        if( !strncmp( pChEv->propertyName().constData(), "TestPropety", strlen("TestPropety")  ) )
        {
            bool x;
            event->accept();
            x = obj->property ( pChEv->propertyName().constData() ).toInt();
            DEBUG(" TestPropety Changed!!! - %s Value=%d", pChEv->propertyName().constData(),x );
            emit debug(x);
        }
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

int EnableQDbg( QDbg* qdb, bool en )
{
    int ret =0;
    if( qdb )
    {
      qdb->logEnable(en);
    }
    else
    {
      ret = 1;
    }
    return ret;
}
int QDbg::ctr;
QDbg::QDbg( const QString &s, QObject *parent) :
    QObject(parent),m_Local(s)
{
   m_ctr = ctr;
   ctr++;
}

QDbg::~QDbg( )
{
  ctr--;
}
void QDbg::log(QString Bla)
{
    if( m_Enable )
    {
        DEBUG() << tr("QDbg%1 [%2]: %3").arg((unsigned int)this).arg(m_Local).arg( Bla );
    }
}


void QDbg::logEnable( bool en )
{
   m_Enable = en;
}
