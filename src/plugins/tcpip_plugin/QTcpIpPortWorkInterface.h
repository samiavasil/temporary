#ifndef SERIALPORTINTERFACE_H
#define SERIALPORTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define SERIAL_PORTIO_VERSION    "V0.0"

class PLUGIN_EXPORT QTcpIpPortWorkInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "QTcpIpPortWorkInterface.json")
#endif
    Q_INTERFACES(QPluginObjectsInterface)
public:
    QTcpIpPortWorkInterface( QObject* parent = 0);
    ~QTcpIpPortWorkInterface(  );

    virtual const char* name() const{
        return "TCP/IP Port IO NAME";
    }
    virtual const char* category() const{
        return "TCP/IP Port IO";
    }
    virtual const char* version() const{
        return SERIAL_PORTIO_VERSION;
    }
    virtual const char* description() const{
        return "TCP/IP Port IO";
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

#endif // SERIALPORTINTERFACE_H
