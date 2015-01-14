#ifndef DATAPLOTINTERFACE_H
#define DATAPLOTINTERFACE_H

#include <QObject>
#include "plugin_global.h"
#include "qt/QPluginObjectsInterface.h"

#define PLOT_VERSION    "V0.0"

class PLUGIN_EXPORT QwtPlotWorkInterface:  public QPluginObjectsInterface
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "vvv.moita.frame_work.QPluginObjectsInterface/1.0" FILE "QwtPlotWorkInterface.json")
#endif
    Q_INTERFACES(QPluginObjectsInterface)
public:
    QwtPlotWorkInterface( QObject* parent = 0);
    ~QwtPlotWorkInterface(  );

    virtual const char* name() const{
        return "QWT Plot NAME";
    }
    virtual const char* category() const{
        return "QWT Plot";
    }
    virtual const char* version() const{
        return PLOT_VERSION;
    }
    virtual const char* description() const{
        return "QWT Plot  ";
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
