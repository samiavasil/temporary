#ifndef PLUGIN_DESCRIPTOR_H
#define PLUGIN_DESCRIPTOR_H
#include "frame_work_global.h"
#include "base/global.h"
#include "QPluginLoaderExt.h"
#include "qt/PluginDescription.h"
#include"qt/QPluginObjectsInterface.h"
#include<QString>
#include<QIcon>
#include<QMutex>
#include<QMessageBox>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

class FRAME_WORKSHARED_EXPORT QPluginFabrique:public QObject{
    Q_OBJECT
public:
    explicit QPluginFabrique( const char *name, QObject* parent = 0 );
    ~QPluginFabrique();

    QObject* cretate_plugin_object( InterfaceType_t pl_type, QObject *parent = 0 );

    const PluginDescription getDescription( ) const
    {
        return m_PluginDecription;
    }

    bool         is_enabled() const{
        return m_enabled;
    }
    void  enable( bool enbl){
        m_enabled = enbl;
        while( state == 3 ){
            QMessageBox msgBox;
            msgBox.setText("Wait For Someting");
            msgBox.exec();
        }
        if( !m_enabled ){
            if( m_loader ){
                m_loader->closeSafety();
                state     = 3;
            }
        }
        else{
            DEBUG << "!!!!!CREATE OBJECT \n";
        }
        DEBUG <<  this;
    }
public slots:
    void allObjectsDestoyed(QObject* obj);

protected:
    void    read_plugin_description();
    QPluginObjectsInterface *cast_to_plugin_interface( QObject* object );

protected:
    QMutex            m_Lock;
    QPluginLoaderExt* m_loader;
    PluginDescription m_PluginDecription;
    bool              m_enabled;
    int               state;
};


void operator<<(  QDebug  Ostr, const QPluginFabrique* in);

#endif // PLUGIN_DESCRIPTOR_H
