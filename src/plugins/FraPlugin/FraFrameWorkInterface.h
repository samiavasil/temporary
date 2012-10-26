#ifndef FRAMEWORKINTERFACE_H
#define FRAMEWORKINTERFACE_H

#include <QObject>
#include <QList>
#include "fra_plugin_global.h"
//#include "interfaces.h"
#include "QFraFrameWork.h"
#include "qt/QPluginObjectsInterface.h"
class QFrameWork;

#define FRA_VERSION    "V0.0"
#include<QDebug>

class FRA_PLUGIN_EXPORT FraFrameWorkInterface: public QObject, public QPluginObjectsInterface
{
    Q_OBJECT
    Q_INTERFACES(QPluginObjectsInterface)
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

virtual void destroy(  );
public slots:
    virtual void frameWorkDestroyed( QObject* fw );
protected:

    virtual  QObject*   allocateObject( QObject* );
    //virtual void destroyObjects(  );
    //void frameWorkDestroyed( QObject* fw );

};

#endif // FRAMEWORKINTERFACE_H
