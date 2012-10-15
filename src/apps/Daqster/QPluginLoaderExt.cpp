#include "QPluginLoaderExt.h"
#include<QDebug>
QList<QPluginLoaderExt*>  QPluginLoaderExt::m_Ploaders;
int QPluginLoaderExt::ctr;

QPluginLoaderExt::QPluginLoaderExt(const QString &fileName,QObject *parent) :
    QPluginLoader(fileName,parent)
{
    m_ctr = ctr;
    qDebug("Create QPluginLoaderExt %d",m_ctr);
    m_Ploaders.append(this);
    m_instance = 0;
    if( isLoaded() ){
        // m_instance = instance();
    }
    ctr++;
}

QPluginLoaderExt::~QPluginLoaderExt(){
    qDebug("Destroy QPluginLoaderExt %d",m_ctr);
    m_Ploaders.takeAt(m_Ploaders.indexOf(this));
    ctr--;
}

QPluginObjectsInterface *QPluginLoaderExt::instance(){
    QObject *instance = (dynamic_cast<QPluginLoader*>(this))->instance();
    /*if( (m_instance)&&(m_instance != instance) ){
        qDebug()<<"!!!Hm - Someting wrong with instance";
    }*/
    m_instance = qobject_cast< QPluginObjectsInterface* >(instance);
    if( m_instance ){
        for( int i=0;i < m_Ploaders.count();i++){
            connect( instance,SIGNAL(destroyed(QObject *)),m_Ploaders[i],SLOT(instanceDestroyed(QObject *)),Qt::QueuedConnection  );
        }
    }
    return m_instance;
}

void QPluginLoaderExt::closeSafety(){
    for( int i=0;i < m_Ploaders.count();i++){
       (m_Ploaders[i])->m_instance->destroy();
    }
}

void QPluginLoaderExt::instanceDestroyed(QObject * obj ){
    if( 0 == obj ){
        qDebug()<<"!!!Hm - Null object";
    }
    else{
        qDebug()<<"Try to unload plugin "<< fileName() << " instance " << m_ctr ;
        unload();
        if( isLoaded() ){
            qDebug()<<"Can't unload plugin  "<< fileName() << " instance " << m_ctr << "Maybe have other instance of QPluginLoader" ;
        }
        else{
            qDebug()<<"Suxessfuly unloaded plugin  "<< fileName() << " instance " << m_ctr;
            //deleteLater();
        }

    }
}
