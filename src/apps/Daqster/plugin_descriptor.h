#ifndef PLUGIN_DESCRIPTOR_H
#define PLUGIN_DESCRIPTOR_H
#include "QPluginLoaderExt.h"
#include "interfaces.h"
#include<QString>
#include<QIcon>
#include <QDebug>

class plugin_descriptor{
public:
    explicit plugin_descriptor( const char *name );
    ~plugin_descriptor();
    inline  QPluginLoaderExt* loader(){
        return m_loader;
    }
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
    const bool         is_enabled() const{
        return m_enabled;
    }
    void               enable( bool enbl){
        m_enabled = enbl;
        qDebug() <<  this;
    }

protected:
    void    read_plugin_description();
    plugin_interface* cast_to_plugin_intrface( QObject* object );
    inline QObject* get_plugin_object( InterfaceType_t type ){
        QObject* object = 0;
        if( !m_Location.isEmpty() ){
            qDebug() << "plugin_descriptor: empty file location";
            return object;
        }
        if(  0 == m_loader  ){
            m_loader = new QPluginLoaderExt( m_Location );
        }
        if( 0 == m_loader ){
            qDebug() << "Can't Load plugin file: " << m_Location;
        }
        return object;
    }
protected:
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
