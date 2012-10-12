#include  <iostream>
#include "plugin_descriptor.h"
#include"qt/QFrameWork.h"
using namespace std;



void operator<<(  QDebug Ostr, const plugin_descriptor* in){
    Ostr <<"===plugin_descriptor:=================================================================\n"
         <<"File Name:   "<<  in->location()   << "\n"
         <<"Category:    "<< in->category()    << "\n"
         <<"Name:        "<< in->name()        << "\n"
         <<"Type:        "<< in->type()        << "\n"
         <<"Description: "<< in->description() << "\n"
         <<"Version:     "<< in->version()     << "\n"
         <<"Enabled:     "<< in->is_enabled()  << "\n"
         <<"===end plugin_descriptor:=============================================================\n";
}

plugin_descriptor::plugin_descriptor( const char *name ){
    m_loader   = 0;
    m_Type     = UNDEFINED;
    m_Location = name;
    read_plugin_description();
}


plugin_descriptor::~plugin_descriptor(){
    if( m_loader ){
        m_loader->deleteLater();
    }
    qDebug() << "Destroy plugin_descriptor:\n" << this;
}


plugin_interface* plugin_descriptor::cast_to_plugin_intrface( QObject* object ){
    plugin_interface* plugin = NULL;
    if( object ){
        plugin = dynamic_cast<plugin_interface *>(qobject_cast<FrameWorkInterface*>(object));
        if( NULL == plugin ){
            plugin = dynamic_cast<plugin_interface *>(qobject_cast<IoInterface*>(object));
            if( NULL == plugin ){
                plugin = dynamic_cast<plugin_interface *>(qobject_cast<AnyTypeInterface*>(object));
            }
        }
    }
    return plugin;
}

void plugin_descriptor::read_plugin_description( ){
    QObject* object;
    plugin_interface* plugin;

    QPluginLoaderExt* loader = new QPluginLoaderExt( m_Location );
    if( 0 != loader ){
        loader->load();
        object =  loader->instance();
        if( 0 != object ){
            plugin = cast_to_plugin_intrface( object );
            if( plugin ){
                m_Type        = plugin->type();
                m_Name        = plugin->name();
                m_Category    = plugin->category();
                m_Version     = plugin->version();
                m_Description = plugin->description();
                m_Icon        = plugin->icon();
            }
            object->deleteLater();
        }
        else{
            qDebug()<<"Can't load object from file " << loader->fileName().toUtf8().constData();
        }
        loader->unload();
        loader->deleteLater();
    }
    else{
        qDebug()<<"Can't create object loader from file " << m_Location.toUtf8().constData();
    }
}
