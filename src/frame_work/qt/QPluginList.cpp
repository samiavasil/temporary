#include <QDir>
#include <QDialog>
#include "interfaces.h"
#include "qt/QPluginList.h"
#include "qt/QFrameWork.h"
#include "qt/QPluginListWidget.h"
#include "ui_pluginlist.h"

QPluginList* QPluginList::m_This = NULL;
QMap< QString, QPluginFabrique*  > QPluginList::m_PluginList;
QPluginList* QPluginList::Instance(){
    DEBUG  << "INPUT" << m_This;
        if( NULL == m_This ){
            m_This = new QPluginList();
        }

    DEBUG  << "OUTPUT" << m_This;
    return m_This;
}


QList<PluginDescription> QPluginList::configurePlugins( const QpluginFilter &filter ){
    if( m_This ){
        QDialog dlg;
        cfgViewTypeT viewType;
        Ui::PluginList *ui = new Ui::PluginList;
        ui->setupUi( &dlg );
        viewType.enable(1).name(1).category(1).location(1);
        QPluginListWidget plw( ui->splitter, filter, viewType );
        ui->splitter->insertWidget(0,&plw);
        connect(ui->reloadButton,SIGNAL(clicked()) ,m_This, SLOT(reloadPlugins()));
        connect( &plw ,SIGNAL(enablePlugin(PluginDescription,bool)) ,m_This, SLOT(pluginEnable(PluginDescription,bool)));
        connect( &plw ,SIGNAL(selectedPluginChanged(PluginDescription)) ,m_This, SLOT(listSelectionChanged(PluginDescription)));
        connect( m_This ,SIGNAL(setDescription(QString)) ,ui->pluginDescription, SLOT(setPlainText(QString)));

        m_This->reloadPlugins();
        dlg.exec();
        return plw.getPluginList();
    }
    else{
        return QList<PluginDescription>();
    }
}

QPluginList::QPluginList(QObject *parent):QObject(parent)
{
    reloadPlugins();
}

QPluginList::~QPluginList()
{
    QMapIterator<QString,QPluginFabrique* > plugin_list(m_PluginList);
    while ( plugin_list.hasNext() ) {
        plugin_list.next();
        if( plugin_list.value() ){
            delete plugin_list.value();
        }
    }
    m_PluginList.clear();
    m_This = NULL;
}


void QPluginList::readPluginsDir( ){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    readDisabledPlugins();
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        fileName = pluginsDir.absoluteFilePath(fileName);
        if(  false == m_PluginList.contains( fileName ) ){
            QPluginFabrique* fab = new QPluginFabrique(fileName.toUtf8().data());
            if( 0 != fab ){
                fab->enable( !is_plugin_disabled( fab->getDescription().name() ) );
                m_PluginList.insert( fileName, fab );
            }
        }
    }
}


void QPluginList::readDisabledPlugins( ){
   //TODO: reading from some configuration DB

}

bool QPluginList::is_plugin_disabled( const QString& name ){
    return false;
}

void QPluginList::pluginEnable( PluginDescription desc, bool enble ){
   //TODO: writing to some configuration DB
    QPluginFabrique* fab = m_PluginList.value( desc.location(), NULL );
    if( fab ){
        fab->enable( enble );
        emit pluginsUpdate();
    }
}

void QPluginList::listSelectionChanged(  const PluginDescription &desc  ){
   emit setDescription(desc.description());
}

void QPluginList::reloadPlugins( ){
    DEBUG << "Reload List";
    readPluginsDir();
   // emit pluginsUpdate();
}


void QPluginList::on_okButton_clicked()
{
    //close();
    //setResult( Accepted );
}

void QPluginList::on_cancelButton_clicked()
{
    //close();
    //setResult( Rejected );
}

QList<PluginDescription> QPluginList::getAllPlugins( const QpluginFilter &filter ){
    QList<PluginDescription> plugin_desc;
    QList<QPluginFabrique*> listPl = m_PluginList.values();
    foreach( QPluginFabrique* pFab, listPl )
    {
      if( pFab && filter.filtered( *pFab ) ){
            plugin_desc.append( pFab->getDescription() );
      }
    }

    return plugin_desc;
}


QObject* QPluginList::cretate_plugin_object( const PluginDescription &desc , QObject *parent )
{

    QObject* object = NULL;
    QList<QPluginFabrique*> listPl = m_PluginList.values();
    foreach( QPluginFabrique* pFab, listPl )
    {
        if(  desc == pFab->getDescription() )
        {
            object = pFab->cretate_plugin_object( parent );
            if( object )
            {
              break;
            }
        }
    }

    return object;
}

