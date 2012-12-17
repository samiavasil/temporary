#ifndef _QPLUGINOBJECTSINTERFACE_H
#define _QPLUGINOBJECTSINTERFACE_H


#include <QList>

#include <QIcon>


#include "interfaces.h"
class FRAME_WORKSHARED_EXPORT QPluginObjectsInterface : public plugin_interface{
  public:
    virtual ~QPluginObjectsInterface();

    QObject* createObject(QObject * obj);

    virtual void destroy() = 0;


  protected:
    virtual QObject* allocateObject(QObject * obj) = 0;

    QList<QObject*> m_fw_objects;

    QIcon m_Icon;

};

Q_DECLARE_INTERFACE(QPluginObjectsInterface,
                    "vvv.moita.frame_work.QPluginObjectsInterface/1.0")
#endif
