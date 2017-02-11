#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define CRYPTO_VERSION    "V0.0"

class PLUGIN_EXPORT QCryptoWorkInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "QCryptoWorkInterface.json")
#endif
    Q_INTERFACES(QPluginObjectsInterface)
public:
    QCryptoWorkInterface( QObject* parent = 0);
    ~QCryptoWorkInterface(  );

    virtual const char* name() const{
        return "QCrypto plugin NAME";
    }
    virtual const char* category() const{
        return "QCrypto plugin";
    }
    virtual const char* version() const{
        return CRYPTO_VERSION;
    }
    virtual const char* description() const{
        return "QCrypto plugin  ";
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

#endif // DATAPLOTINTERFACE_H
