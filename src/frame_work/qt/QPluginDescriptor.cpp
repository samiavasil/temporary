#include  <iostream>
#include "qt/QPluginDescriptor.h"
#include"qt/QFrameWork.h"

void operator<<(  QDebug Ostr, const QPluginDescriptor* in){
    Ostr <<"===plugin_descriptor:=================================================================\n"
        <<"File Name:   "<<  in->getDescription().location()   << "\n"
       <<"Category:    "<< in->getDescription().category()    << "\n"
      <<"Name:        "<< in->getDescription().name()        << "\n"
     <<"Type:        "<< in->getDescription().type()        << "\n"
    <<"Description: "<< in->getDescription().description() << "\n"
    <<"Version:     "<< in->getDescription().version()     << "\n"
    <<"Enabled:     "<< in->is_enabled()  << "\n"
    <<"===end plugin_descriptor:=============================================================\n";
}

QPluginDescriptor::QPluginDescriptor( const char *name, QObject *parent ):
    QObject( parent ), m_PluginDecription(UNDEFINED,name)
{
    state        = 0;
    m_enabled    = true;
    m_loader     = 0;

    read_plugin_description();

}

QPluginDescriptor::~QPluginDescriptor(){
    m_enabled = false;
    if( m_loader ){
        m_loader->deleteLater();
    }
    DEBUG() << "Destroy plugin_descriptor:\n" << this;
}

QPluginObjectsInterface* QPluginDescriptor::cast_to_plugin_interface( QObject* object ){
    QPluginObjectsInterface* plugin = NULL;
    if( object ){
        plugin =  qobject_cast< QPluginObjectsInterface* >(object);
    }
    return plugin;
}

void QPluginDescriptor::read_plugin_description( ){

    QPluginObjectsInterface* plugin;
    QPluginLoaderExt* loader = new QPluginLoaderExt( m_PluginDecription.location() );
    if( 0 != loader ){
        loader->load();
        plugin =  loader->instance();
        if( plugin ){
            m_PluginDecription = PluginDescription(
                                        plugin->type(),
                                        m_PluginDecription.location(),
                                        plugin->name(),
                                        plugin->category(),
                                        plugin->version(),
                                        plugin->description(),
                                        plugin->icon()
                                    );

            delete plugin;
        }
        else{
            DEBUG()<<"Can't load object from file " << loader->fileName().toUtf8().constData();
        }
        loader->unload();
        delete loader;
    }
    else{
        DEBUG()<<"Can't create object loader from file " << m_PluginDecription.location().toUtf8().constData();
    }
}

QObject* QPluginDescriptor::cretate_plugin_object( InterfaceType_t pl_type, QObject* parent  ){
    QObject* object = 0;

    if( !m_enabled ){
        DEBUG() << "plugin_disabled: can't create object";
        return object;
    }
    if( m_PluginDecription.location().isEmpty() ){
        DEBUG() << "plugin_descriptor: empty file location";
        return object;
    }
    if( pl_type == m_PluginDecription.type() ){
        QPluginLoaderExt* loader;
        if( m_loader ){
            loader = m_loader;
        }
        else{
            loader = new QPluginLoaderExt( m_PluginDecription.location() );
        }
        if( loader ){
            loader->load();
            QPluginObjectsInterface* fW =  loader->instance();
            if( fW ){
                object =  fW->createObject( parent );
                if( 0 != object ){
                    m_loader = loader;
                    connect( m_loader, SIGNAL( allObjectsDestroyed( QObject* ) ), this, SLOT( loaderDestroyed( QObject* ) ),Qt::DirectConnection );
                }
                else{
                    loader->deleteLater();
                }
            }
            else{
                loader->deleteLater();
            }
        }
    }
    if( 0 == object ){
        DEBUG() << "\nCan't create obect from plugin file: " << m_PluginDecription.location();
    }
    return object;
}

void QPluginDescriptor::loaderDestroyed( QObject* obj ){
    if( m_loader == dynamic_cast<QPluginLoaderExt*>(obj)   ){
        m_loader->deleteLater();
        m_loader  = NULL;
        state = 0;
    }
}
