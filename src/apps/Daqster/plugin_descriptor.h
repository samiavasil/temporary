#ifndef PLUGIN_DESCRIPTOR_H
#define PLUGIN_DESCRIPTOR_H
#include "QPluginLoaderExt.h"
//#include "interfaces.h"
#include"qt/QpluginObjectsInterface.h"
#include<QString>
#include<QIcon>
#include <QDebug>
#include<QMutex>

class plugin_descriptor{
public:
    explicit plugin_descriptor( const char *name );
    ~plugin_descriptor();

    QObject* cretate_plugin_object( InterfaceType_t type, QObject *parent = 0 );

    InterfaceType_t    type() const{
        return   m_Type;
    }
    const QString&     name() const{
        return   m_Name;
    }
    const QString&     category() const{
        return   m_Category;
    }
    const QString&     version() const{
        return   m_Version;
    }
    const QString&     description() const{
        return   m_Description;
    }
    const QString&     location() const{
        return m_Location;
    }
    const QIcon        icon() const{
        return   m_Icon;
    }
    bool         is_enabled() const{
        return m_enabled;
    }
    void  enable( bool enbl){
        m_enabled = enbl;
        if( !m_enabled ){
            if( m_loader ){
              m_loader->closeSafety();
            }
        }
        else{
            cretate_plugin_object( type() , NULL );//DELL ME
        }
        qDebug() <<  this;
    }

protected:
    void    read_plugin_description();
    QPluginObjectsInterface *cast_to_plugin_interface( QObject* object );

protected:
    QMutex            m_Lock;
    QPluginLoaderExt* m_loader;
    InterfaceType_t   m_Type;
    QString           m_Name;
    QString           m_Location;
    QString           m_Category;
    QString           m_Version;
    QString           m_Description;
    QIcon             m_Icon;
    bool              m_enabled;
};


void operator<<(  QDebug  Ostr, const plugin_descriptor* in);

#endif // PLUGIN_DESCRIPTOR_H
