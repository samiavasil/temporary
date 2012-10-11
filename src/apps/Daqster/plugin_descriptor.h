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
    InterfaceType_t    type() const;
    const QString&     name() const;
    const QString&     category() const;
    const QString&     version() const;
    const QString&     description() const;
    const QString&     location() const;
    const QIcon        icon() const;
    const bool         is_enabled() const;
    void               enable( bool enbl);
protected:
    void    read_plugin_description();
    plugin_interface* cast_to_plugin_intrface( QObject* object );
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
