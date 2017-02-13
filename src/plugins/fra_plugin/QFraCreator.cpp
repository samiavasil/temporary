#include "base/global.h"
#include "QFraCreator.h"
#include "QFraFrameWork.h"
#include "QPortsIoView.h"
#include "qt/QPluginList.h"
#include <unistd.h>

QFraCreator::QFraCreator(QObject *parent):QCreator(parent),m_qfW( NULL )
{

}

QFraCreator::~QFraCreator( )
{
    if( m_qfW ){
        m_qfW->deleteLater();
    }
}
#include<QStringList>
#include <QMetaMethod>

#define TEST_META_METHODS_DUMP
#if defined( TEST_META_METHODS_DUMP ) /*TODO: move from here*/
void dump_qobject_meta( QObject* obj ){

    if( !obj ) return;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    const QMetaObject* metaObject = obj->metaObject();
    DEBUG <<"DUMP METHODS:   "<<endl;
    for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
    {
        DEBUG <<   QString("QFraFrameWork[%1]").arg(random());
        DEBUG <<"   "<<QString::fromLatin1(metaObject->method(i).signature());
        if( -1 == metaObject->indexOfSignal( metaObject->method(i).signature() ) )
        {
            DEBUG << ":  Method Not signal";
        }
        else
        {
            DEBUG << ":  Its a signal";
            if( metaObject->checkConnectArgs ( "testSlot()", metaObject->method(i).signature() ) )
            {
                DEBUG  << "==> Compatible with slot testSlot";
            }
            else
            {
                DEBUG  << "==> Not Compatible with slot testSlot";
            }
        }
        DEBUG << endl;
    }
#endif
}
#endif

#include "QFraDeviceUI.h"
bool QFraCreator::Create( CFrameWork *fW )
{
    bool bRet = false;
 //   QPluginList::configurePlugins( );
    if( fW )
    {
        m_qfW =  dynamic_cast<QFraFrameWork*>(fW);
        DEBUG <<   tr("QFraFrameWork[%1]").arg(qrand());
        if( m_qfW )
        {
            QWidget* fw_win = m_qfW->getFrameWorkWindow();

            //QpluginFilter filter( UNDEFINED );
            QList<PluginDescription> list = QPluginList::Instance()->getAllPlugins( QPluginFilter( DATA_OUT ) );
            QFraDeviceUI* fra_dev = new QFraDeviceUI(fw_win);
            m_qfW->AddWidgetToControlArrea(fra_dev);

#if 0
            foreach( PluginDescription desc,list ){
                {
                    QObject* obj;
                    for( int i=0;i<10;i++){


                        obj = QPluginList::Instance()->cretate_plugin_object( desc , m_qfW );
                        if( obj )
                        {
                            m_qfW->AddWidgetToDataViewArrea( dynamic_cast<QWidget*>(obj) );
                        }
#if defined( TEST_META_METHODS_DUMP ) /*TODO: move from here*/
                        dump_qobject_meta( obj );
#endif
                    }

            }
#endif

            if( fw_win ){
                fw_win->show();
            }

        }
    }

    return bRet;
}

void QFraCreator::Free()
{

}
