#ifndef VDESIGNERINTERFACE_H
#define VDESIGNERINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define DES_VERSION    "V0.0"

namespace Plugins
{


class PLUGIN_EXPORT VDesignerInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
    Q_INTERFACES(QPluginObjectsInterface)
public:
    VDesignerInterface( QObject* parent = 0);
    ~VDesignerInterface( );

    virtual const char* name() const{
        return "VDesigner NAME";
    }
    virtual const char* category() const{
        return "VDesigner Plot";
    }
    virtual const char* version() const{
        return DES_VERSION;
    }
    virtual const char* description() const{
        return "VDesigner Plot  ";
    }
    virtual QIcon    const   icon() const {
        return m_Icon;
    }
    virtual  InterfaceType_t type(){
       return FRAME_WORK;
    }

protected:
    virtual  QObject*   allocateObject( QObject* );
};
}
#endif // VDESIGNERINTERFACE_H
