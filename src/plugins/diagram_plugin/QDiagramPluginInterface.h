#ifndef DIAGRAM_PLUGIN_INTERFACE_H
#define DIAGRAM_PLUGIN_INTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define DIAGRAM_PLUGIN_VERSION    "V0.0"

class PLUGIN_EXPORT QDiagramPluginInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "QDiagramPluginInterface .json")
#endif
    Q_INTERFACES(QPluginObjectsInterface)
public:
    QDiagramPluginInterface( QObject* parent = 0);
    ~QDiagramPluginInterface(  );

    virtual const char* name() const{
        return "Diagram Plugin";
    }
    virtual const char* category() const{
        return "Diagram Plot";
    }
    virtual const char* version() const{
        return DIAGRAM_PLUGIN_VERSION;
    }
    virtual const char* description() const{
        return "Diagram Plot  ";
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

#endif // DIAGRAM_PLUGIN_INTERFACE_H
