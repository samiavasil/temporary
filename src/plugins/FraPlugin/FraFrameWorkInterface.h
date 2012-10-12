#ifndef FRAMEWORKINTERFACE_H
#define FRAMEWORKINTERFACE_H

#include <QObject>
#include <QList>
#include "fra_plugin_global.h"
#include "interfaces.h"
#include "QFraFrameWork.h"
class QFrameWork;

#define FRA_VERSION    "V0.0"
#include<QDebug>

class FRA_PLUGIN_EXPORT FraFrameWorkInterface: public QObject, public FrameWorkInterface
{
    Q_OBJECT
    Q_INTERFACES(FrameWorkInterface)
public:
    FraFrameWorkInterface(QObject* parent=0);
    ~FraFrameWorkInterface(  );
    //virtual  QFrameWork* getFrameWork( QWidget *parent  );
    virtual  QObject*         createObject( QObject* );
    virtual const char* name() const     {return "FRA NAME";}
    virtual  InterfaceType_t type()      {
       return FRAME_WORK;
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


public slots:
    void frameWorkDestroyed( QObject* fw );
protected:
    QIcon m_Icon;
    QList<QObject*> m_fw_objects;
};

#endif // FRAMEWORKINTERFACE_H
