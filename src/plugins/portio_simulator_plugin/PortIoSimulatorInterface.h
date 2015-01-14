#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define PLOT_VERSION    "V0.0"

class PLUGIN_EXPORT PortIoSimulatorInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "PortIoSimulatorInterface.json")
#endif
    Q_INTERFACES(QPluginObjectsInterface)
public:
    PortIoSimulatorInterface( QObject* parent = 0);
    ~PortIoSimulatorInterface(  );

    virtual const char* name() const{
        return "Simulator Port IO NAME";
    }
    virtual const char* category() const{
        return "Simulator Port IO";
    }
    virtual const char* version() const{
        return PLOT_VERSION;
    }
    virtual const char* description() const{
        return "Simulator PortIO  ";
    }
    virtual QIcon    const   icon() const {
        return m_Icon;
    }
    virtual  InterfaceType_t type(){
       return PORT_IO;
    }

protected:
    virtual  QObject*   allocateObject( QObject* );
};

#endif // DATAPLOTINTERFACE_H
