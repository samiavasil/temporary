#include "qt/QPluginObjectsInterface.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QPluginObjectsInterface::QPluginObjectsInterface(QObject * parent):QObject(parent){
}

QPluginObjectsInterface::~QPluginObjectsInterface() {
}

QObject* QPluginObjectsInterface::createObject(QObject * obj) {
  QObject* ret_obj = allocateObject( obj );

  if( 0 != ret_obj ){
      ret_obj->setObjectName( name() );
      m_fw_objects.append( ret_obj );
      connect( ret_obj,SIGNAL(destroyed(QObject*)), this, SLOT(objectDestroyed(QObject*)),Qt::QueuedConnection);
  }
  return ret_obj;
}

void QPluginObjectsInterface::destroyPI() {
  for( int i=0; i < m_fw_objects.count(); i++ ){
      if( m_fw_objects[i] ){
          m_fw_objects[i]->deleteLater();
      }
  }
}

void QPluginObjectsInterface::objectDestroyed(QObject * obj) {
    if(  obj && m_fw_objects.contains(  obj ) ){
        DEBUG << "Remove from list Destroyed QFraFrameWork[" << (void *)obj << "]";
        m_fw_objects.takeAt(m_fw_objects.indexOf( obj ));
        DEBUG << "On List " << m_fw_objects.count();
        if( 0 == m_fw_objects.count() ){
           deleteLater();
        }
    }
}

