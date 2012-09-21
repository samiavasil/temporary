#ifndef FRAMEWORKINTERFACE_H
#define FRAMEWORKINTERFACE_H

#include <QObject>
#include <QStringList>
#include "fra_plugin_global.h"
#include "interfaces.h"
class QFrameWork;

class FRA_PLUGIN_EXPORT frameworkinterface: public QObject, public FrameWorkInterface
{
    Q_OBJECT
    Q_INTERFACES(FrameWorkInterface)
public:
    frameworkinterface(QObject* parent=0);
    ~frameworkinterface(  );
    virtual  QFrameWork* getFrameWork( QWidget *parent  );
    virtual const char* name() const       {return nameto;}

    virtual const FrameWorktInterfaces_t type(){return FRAME_WORK;}
protected:
    char nameto[100];
};

#endif // FRAMEWORKINTERFACE_H
