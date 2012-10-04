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

QObject * QPluginLoaderExt::instance(){
    QObject *instance = QPluginLoader::instance();
    m_instance = instance;
    for( int i=0;i<m_Ploaders.count();i++){
       connect( m_instance,SIGNAL(destroyed(QObject *)),m_Ploaders[i],SLOT(instanceDestroyed(QObject *)),Qt::QueuedConnection  );
    }
    return m_instance;
}

void QPluginLoaderExt::instanceDestroyed(QObject * obj ){
    if( 0 == obj ){
        qDebug()<<"!!!Hm - Null object";
    }
    else{
        qDebug()<<"Instance destroyed free plugin "<< fileName() << " instance " << m_ctr ;
        if( isLoaded() ){//DELL ME
            qDebug()<<"Plugin is loaded  "<< fileName() << " instance " << m_ctr ;
            unload();
        }

        if( isLoaded() ){
            qDebug()<<"Can't free plugin  "<< fileName() << " instance " << m_ctr ;
        }
        else{
            qDebug()<<"Unload plugin suxess  "<< fileName() << " instance " << m_ctr ;
            deleteLater();
        }
    }
}
