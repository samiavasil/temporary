#ifndef _QPLUGINOBJECTSINTERFACE_H
#define _QPLUGINOBJECTSINTERFACE_H


#include <QList>

#include <QIcon>


#include "interfaces.h"
class FRAME_WORKSHARED_EXPORT QPluginObjectsInterface :public QObject, public plugin_interface{
    Q_OBJECT
  public:
    QPluginObjectsInterface(QObject* parent);
    virtual ~QPluginObjectsInterface();

    QObject* createObject(QObject * obj);

    virtual void destroyPI(  );
 public slots:
        virtual void objectDestroyed( QObject* fw );
  protected:
    virtual QObject* allocateObject(QObject * obj) = 0;

    QList<QObject*> m_fw_objects;

    QIcon m_Icon;

};

Q_DECLARE_INTERFACE(QPluginObjectsInterface,
                    "vvv.moita.frame_work.QPluginObjectsInterface/1.0")
#endif
