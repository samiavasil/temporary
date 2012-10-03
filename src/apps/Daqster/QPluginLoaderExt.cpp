#include "QPluginLoaderExt.h"

QPluginLoaderExt::QPluginLoaderExt(QObject *parent) :
    QPluginLoader(parent)
{
    m_instance = 0;
}

QObject * QPluginLoaderExt::instance(){
    QObject *instance = QPluginLoader::instance();
    if( ( 0 == m_instance )&&( instance != m_instance ) ){
        qDebug("!!!Hm - Misterious: m_instance here should be 0");
    }
    m_instance = instance;
    connect( m_instance,SIGNAL(destroyed(QObject *)),this,SLOT(instanceDestroyed(QObject * obj ))  );
    return m_instance;
}

void QPluginLoaderExt::instanceDestroyed(QObject * obj ){
    if( (0 == obj)||( obj != m_instance ) ){
        qDebug("!!!Hm - Misterious instance is conected to instanceDestroyed");
    }
    else{
        qDebug("Instance destroyed free plugin");

    }
    //obj->children()
}
