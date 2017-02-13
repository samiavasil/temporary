#ifndef FRAMEWORKINTERFACE_H
#define FRAMEWORKINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define FRA_VERSION    "V0.0"
#include "qt/QLoggerInterface.h"

class PLUGIN_EXPORT FraFrameWorkInterface:  public QPluginObjectsInterface, public QLoggerInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "FraFrameWorkInterface.json")
#endif
    Q_INTERFACES( QPluginObjectsInterface )
public:
    FraFrameWorkInterface( QObject* parent = 0);
    ~FraFrameWorkInterface(  );

    virtual const char* name() const{
        return "FRA NAME";
    }
    virtual const char* category() const{
        return "FrameWork";
    }
    virtual const char* version() const{
        return FRA_VERSION;
    }
    virtual const char* description() const{
        return "Frequency Response Analyzer\n This softwer is a nekaw software.\rProba ";
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

#endif // FRAMEWORKINTERFACE_H
