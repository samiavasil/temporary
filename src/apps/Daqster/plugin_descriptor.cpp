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

plugin_descriptor::plugin_descriptor( const char *name, QObject *parent ):QObject( parent ){
    m_enabled  = true;
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


QPluginObjectsInterface* plugin_descriptor::cast_to_plugin_interface( QObject* object ){
    QPluginObjectsInterface* plugin = NULL;
    if( object ){
        plugin =  qobject_cast< QPluginObjectsInterface* >(object);
    }
    return plugin;
}

void plugin_descriptor::read_plugin_description( ){

    QPluginObjectsInterface* plugin;
    QPluginLoaderExt* loader = new QPluginLoaderExt( m_Location );
    if( 0 != loader ){
        loader->load();
        plugin =  loader->instance();
        if( plugin ){
            m_Type        = plugin->type();
            m_Name        = plugin->name();
            m_Category    = plugin->category();
            m_Version     = plugin->version();
            m_Description = plugin->description();
            m_Icon        = plugin->icon();
            delete plugin;
        }
        else{
            qDebug()<<"Can't load object from file " << loader->fileName().toUtf8().constData();
        }
        loader->unload();
        delete loader;
    }
    else{
        qDebug()<<"Can't create object loader from file " << m_Location.toUtf8().constData();
    }
}


QObject* plugin_descriptor::cretate_plugin_object( InterfaceType_t type, QObject* parent  ){
    QObject* object ;

    if( !m_enabled ){
        qDebug() << "plugin_disabled: can't create object";
        return object;
    }
    if( m_Location.isEmpty() ){
        qDebug() << "plugin_descriptor: empty file location";
        return object;
    }
    if( type == m_Type ){
        QPluginLoaderExt* loader;

        if( m_loader ){
            loader = m_loader;
        }
        else{
            loader = new QPluginLoaderExt( m_Location );
        }
        if( loader ){
            loader->load();
            QPluginObjectsInterface* fW =  loader->instance();
            object =  fW->createObject( parent );
            dynamic_cast<QWidget*>(object)->show();//DELL ME
            /*if( fW ){
                switch( type ){
                case FRAME_WORK:{
                    object =  fW->createObject( parent );
                    dynamic_cast<QWidget*>(object)->show();
                    break;
                }
                case PORT_IO:{
                    //   IoInterface* fW = qobject_cast<IoInterface*>( interface_object );
                    //    object =  fW->createObject( parent );
                    break;
                }
                default:{
                    break;
                }
                }
            }*/
            if( 0 != object ){
                m_loader = loader;
                connect( m_loader, SIGNAL( destroyed( QObject* ) ), this, SLOT( loaderDestroyed( QObject* ) ) );
            }
            else{
                loader->deleteLater();
            }
        }
    }
    if( 0 == object ){
        qDebug() << "\nCan't create obect from plugin file: " << m_Location;
    }
    return object;
}

void plugin_descriptor::loaderDestroyed( QObject* obj ){
    if( obj == dynamic_cast<QObject*>( m_loader ) ){
        m_loader = NULL;
    }
}
