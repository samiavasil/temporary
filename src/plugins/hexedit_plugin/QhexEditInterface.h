#ifndef HEXEDITINTERFACE_H
#define HEXEDITINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define HEXEDIT_VERSION    "V0.0"

class PLUGIN_EXPORT QhexEditInterface:  public QPluginObjectsInterface
{

    Q_INTERFACES(QPluginObjectsInterface)
public:
    QhexEditInterface( QObject* parent = 0);
    ~QhexEditInterface(  );

    virtual const char* name() const{
        return "HexEdit NAME";
    }
    virtual const char* category() const{
        return "HexEdit";
    }
    virtual const char* version() const{
        return HEXEDIT_VERSION;
    }
    virtual const char* description() const{
        return "HexEdit  ";
    }
    virtual QIcon    const   icon() const {
        return m_Icon;
    }
    virtual  InterfaceType_t type(){
       return DATA_OUT;
    }

protected:
    virtual  QObject*   allocateObject( QObject* );
};

#endif // HEXEDITINTERFACE_H
