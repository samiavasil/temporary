
#include "qt/QPluginObjectsInterface.h"
#include <QObject>


QPluginObjectsInterface::~QPluginObjectsInterface() {
}

QObject* QPluginObjectsInterface::createObject(QObject * obj) {
  QObject* ret_obj = allocateObject( obj );
  if( 0 != ret_obj ){
      m_fw_objects.append( ret_obj );
  }
  return ret_obj;
}

