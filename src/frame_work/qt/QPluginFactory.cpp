#include  <iostream>
#include "qt/QPluginFactory.h"
#include"qt/QFrameWork.h"

void operator<<(  QDebug Ostr, const QPluginFactory* in){
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

QPluginFactory::QPluginFactory( const char *name, QObject *parent ):
    QObject( parent ), m_PluginDecription(UNDEFINED,name)
{
    state        = 0;
    m_loader     = 0;
    read_plugin_description();

}

QPluginFactory::~QPluginFactory(){
    m_PluginDecription.enable( false );
    if( m_loader ){
        m_loader->deleteLater();
    }
    DEBUG  << "Destroy plugin_descriptor:\n" << this;
}

QPluginObjectsInterface* QPluginFactory::cast_to_plugin_interface( QObject* object ){
    QPluginObjectsInterface* plugin = NULL;
    if( object ){
        plugin =  qobject_cast< QPluginObjectsInterface* >(object);
    }
    return plugin;
}

void QPluginFactory::read_plugin_description( ){

    QPluginObjectsInterface* pluginObj;
    QPluginLoaderExt* loader = new QPluginLoaderExt( m_PluginDecription.location() );
    DEBUG <<m_PluginDecription.location();
    if( 0 != loader ){
        loader->load();
        pluginObj =  loader->instance();
        if( pluginObj ){
            m_PluginDecription = PluginDescription(
                                        pluginObj->type(),
                                        m_PluginDecription.location(),
                                        pluginObj->name(),
                                        pluginObj->category(),
                                        pluginObj->version(),
                                        pluginObj->description(),
                                        pluginObj->icon()
                                    );

            delete pluginObj;
        }
        else{
            DEBUG <<"Can't load object from file " << loader->fileName().toUtf8().constData();
        }
        loader->unload();
        delete loader;
    }
    else{
        DEBUG <<"Can't create object loader from file " << m_PluginDecription.location().toUtf8().constData();
    }
}

QObject* QPluginFactory::cretate_plugin_object( QObject* parent  ){
    QObject* object = 0;

    if( !is_enabled() ){
        DEBUG  << "plugin_disabled: can't create object";
        return object;
    }
    if( m_PluginDecription.location().isEmpty() ){
        DEBUG  << "plugin_descriptor: empty file location";
        return object;
    }
    QPluginLoaderExt* loader;
    if( m_loader ){
        loader = m_loader;
    }
    else{
        loader = new QPluginLoaderExt( m_PluginDecription.location() );
    }
    if( loader ){
        loader->load();
        QPluginObjectsInterface* ObjInt =  loader->instance();
        if( ObjInt ){
            object =  ObjInt->createObject( parent );
            if( 0 != object ){
                m_loader = loader;
                connect( m_loader, SIGNAL( allObjectsDestroyed( QObject* ) ), this, SLOT( allObjectsDestoyed( QObject* ) ),Qt::DirectConnection );
            }
            else{
                loader->deleteLater();
            }
        }
        else{
            loader->deleteLater();
        }
    }

    if( 0 == object ){
        DEBUG  << "\nCan't create obect from plugin file: " << m_PluginDecription.location();
    }
    return object;
}

void QPluginFactory::allObjectsDestoyed( QObject* obj ){
    if( m_loader == dynamic_cast<QPluginLoaderExt*>(obj)   ){
        m_loader->deleteLater();
        m_loader  = NULL;
        state = 0;
    }
}

void  QPluginFactory::enable( bool enbl){
    m_PluginDecription.enable( enbl );
    while( state == 3 ){
        QMessageBox msgBox;
        msgBox.setText("Wait For Someting");
        msgBox.exec();
    }
    if( !enbl ){
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

bool  QPluginFactory::is_enabled() const{
    return m_PluginDecription.is_enabled();
}
