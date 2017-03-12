#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "Daqster/QPluginBaseInterface.h"


class PLUGIN_EXPORT DaqsterTeplateInterface:  public Daqster::QPluginBaseInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "Daqster.PlugIn.BaseInterface" FILE "DaqsterTeplateInterface.json")
#endif
    Q_INTERFACES(Daqster::QPluginBaseInterface)
public:
    DaqsterTeplateInterface( QObject* parent = 0);
    ~DaqsterTeplateInterface(  );
protected:
    virtual Daqster::QBasePluginObject* createPluginInternal(QObject* Parrent = NULL);
};

#endif // DATAPLOTINTERFACE_H
