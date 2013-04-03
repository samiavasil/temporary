#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define DATA_PLOT_VERSION    "V0.0"

class PLUGIN_EXPORT DataPlotWorkInterface:  public QPluginObjectsInterface
{

    Q_INTERFACES(QPluginObjectsInterface)
public:
    DataPlotWorkInterface( QObject* parent = 0);
    ~DataPlotWorkInterface(  );

    virtual const char* name() const{
        return "DATA Plot";
    }
    virtual const char* category() const{
        return "DATA Plot";
    }
    virtual const char* version() const{
        return DATA_PLOT_VERSION;
    }
    virtual const char* description() const{
        return "DATA Plot  ";
    }
    virtual QIcon    const   icon() const {
        return m_Icon;
    }
    virtual  InterfaceType_t type(){
       return DATA_PLOT;
    }

protected:
    virtual  QObject*   allocateObject( QObject* );
};

#endif // DATAPLOTINTERFACE_H
