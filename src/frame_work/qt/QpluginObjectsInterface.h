#ifndef QPLUGINOBJECTSINTERFACE_H
#define QPLUGINOBJECTSINTERFACE_H


#include "interfaces.h"

class FRAME_WORKSHARED_EXPORT QPluginObjectsInterface : public plugin_interface
{
public:
    virtual ~QPluginObjectsInterface( ) {
    }
    virtual  QObject*   createObject( QObject* obj ){
        QObject* ret_obj = allocateObject( obj );
        if( 0 != ret_obj ){
            m_fw_objects.append( ret_obj );
        }
        return ret_obj;
    }
virtual void destroy(  ) = 0;
    virtual int unloadAllObjects() = 0;
protected:
    virtual  QObject*   allocateObject( QObject* ) = 0;
protected:
    QIcon m_Icon;
    QList<QObject*> m_fw_objects;
};

Q_DECLARE_INTERFACE(QPluginObjectsInterface,
                    "vvv.moita.frame_work.QPluginObjectsInterface/1.0")

#endif // QPLUGINOBJECTSINTERFACE_H
