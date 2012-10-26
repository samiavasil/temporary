
#include "qt/QPluginLoaderExt.h"
#include <QObject>

#include "qt/QPluginObjectsInterface.h"
#include<QDebug>
QMultiMap<QString, QPluginLoaderExt*> QPluginLoaderExt::m_Ploaders;

/**
 * DELL ME
 */
int QPluginLoaderExt::ctr;

QPluginLoaderExt::QPluginLoaderExt(const QString & fileName, QObject * parent):
    QPluginLoader(fileName,parent ) {
  m_ctr = ctr;
  qDebug() << "Create QPluginLoaderExt " << m_ctr << "  " << fileName;
  m_Ploaders.insert( fileName, this );
  m_instance = 0;
  if( isLoaded() ){
      // m_instance = instance();
  }
  ctr++;
}

QPluginLoaderExt::~QPluginLoaderExt() {
  qDebug( ) << "!!!!!!!!!!!!!!!!!!Destroy QPluginLoaderExt " << m_ctr << fileName();
  m_Ploaders.remove( fileName(), this );
  // ctr--;
}

void QPluginLoaderExt::closeSafety() {
  QMap<QString, QPluginLoaderExt*>::iterator i = m_Ploaders.find ( fileName()  );
  while( ( i != m_Ploaders.end()) && (i.key() == fileName() ) ) {
      qDebug()<<i.key();
      if( i.value() && i.value()->m_instance ){
          i.value()->m_instance->destroy();
      }
      ++i;
  }
}

QPluginObjectsInterface* QPluginLoaderExt::instance() {
  QObject *instance = (dynamic_cast<QPluginLoader*>(this))->instance();
  m_instance = qobject_cast< QPluginObjectsInterface* >(instance);
  if( m_instance ){
      QMap<QString, QPluginLoaderExt*>::iterator i = m_Ploaders.find ( fileName() );
      while( ( i != m_Ploaders.end() ) && (i.key() == fileName() ) ) {
          qDebug()<<i.key();
          connect( instance, SIGNAL(destroyed(QObject *)), i.value(), SLOT(instanceDestroyed(QObject *)), Qt::QueuedConnection );
          ++i;
      }
  }
  return m_instance;
}

void QPluginLoaderExt::instanceDestroyed(QObject * obj) {
  if( 0 == obj ){
      qDebug()<<"!!!Hm - Null object";
  }
  else{
      if( isLoaded() ){
          qDebug()<<"Try to unload plugin "<< fileName() << " instance " << m_ctr ;
          unload();
          if( isLoaded() ){
              qDebug()<<"Can't unload plugin  "<< fileName() << " instance " << m_ctr << "Maybe have other instance of QPluginLoader" ;
          }
          else{
              qDebug()<<"Suxessfuly unloaded plugin  "<< fileName() << " instance " << m_ctr;
              emit allObjectsDestroyed( this );
          }
      }
  }
}

