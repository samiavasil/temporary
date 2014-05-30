#include "qt/QPluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QDir>
#include "qt/QFrameWork.h"

QPluginList* QPluginList::m_This = NULL;
QMap< QString, QPluginFabrique*  > QPluginList::m_PluginList;
QPluginList* QPluginList::Instance()
{
    DEBUG  << "INPUT" << m_This;
        if( NULL == m_This )
        {
            m_This = new QPluginList();
        }

    DEBUG  << "OUTPUT" << m_This;
    return m_This;
}

QPluginList::QPluginList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginList)
{
    ui->setupUi(this);

    //populatePluginList();
    ui->availablePlugins->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availablePlugins->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->availablePlugins,SIGNAL(itemChanged(QTableWidgetItem*) ),this, SLOT(listSelectionChanged(QTableWidgetItem*)));
    connect(this,SIGNAL(reload()) ,this, SLOT(reloadPlugins()));
    connect(ui->reloadButton,SIGNAL(clicked()) ,this, SLOT(reloadPlugins()));
    emit reload();
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
    delete ui;
    m_This = NULL;
}


void QPluginList::readPluginsDir( ){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        fileName = pluginsDir.absoluteFilePath(fileName);
        if(  false == m_PluginList.contains( fileName ) ){
            QPluginFabrique* fab = new QPluginFabrique(fileName.toUtf8().data());
            if( 0 != fab ){
                m_PluginList.insert( fileName, fab );
            }
        }
    }
    populatePluginList();
}

#define LOCATION_COLUMN 2
void QPluginList::populatePluginList(){
    int i =0;
    ui->availablePlugins->clear();
    ui->availablePlugins->setRowCount(0);
    ui->availablePlugins->setColumnCount(3);
    QMapIterator<QString,QPluginFabrique* > plugin_list(m_PluginList);
    while ( plugin_list.hasNext() ) {
        plugin_list.next();
        QPluginFabrique* desc = plugin_list.value();
        if( desc ){
            DEBUG  <<  desc;
            ui->availablePlugins->insertRow( i );
            QTableWidgetItem *item = new QTableWidgetItem( desc->getDescription().name() );
            if( !desc->getDescription().icon().isNull() ){
                QIcon icon = desc->getDescription().icon();
                item->setIcon( icon );
            }
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->availablePlugins->setItem( i, 0, item );

            item = new QTableWidgetItem(desc->getDescription().category());
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->availablePlugins->setItem( i, 1, item );

            item = new QTableWidgetItem( desc->getDescription().location() );
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
            item->setCheckState ( Qt::Checked );
            ui->availablePlugins->setItem( i, LOCATION_COLUMN, item );
            i++;
        }
    }
}

void QPluginList::listSelectionChanged( QTableWidgetItem* item ){

    int row = ui->availablePlugins->row(item);
    QTableWidgetItem* item_location = ui->availablePlugins->item( row, LOCATION_COLUMN );
    if( item_location && m_PluginList.contains( item_location->text() ) ){
        if(  Qt::Checked == item_location->checkState() ){
            if( !m_PluginList[item_location->text()]->is_enabled() ){
                m_PluginList[item_location->text()]->enable( true );
            }
        }
        else{
            if( m_PluginList[item_location->text()]->is_enabled() ){
                m_PluginList[item_location->text()]->enable( false );
            }
        }
    }
}

void QPluginList::reloadPlugins( ){
    DEBUG << "Reload List";
    ui->availablePlugins->blockSignals(true);
    readPluginsDir();
    ui->availablePlugins->blockSignals(false);
}


void QPluginList::on_okButton_clicked()
{
    close();
    setResult( Accepted );
}

void QPluginList::on_cancelButton_clicked()
{
    close();
    setResult( Rejected );
}

QList<PluginDescription> QPluginList::getAllActivePlugins( InterfaceType_t type ){
    QList<PluginDescription> plugin_desc;
    reloadPlugins();
    type = type;
    QList<QPluginFabrique*> listPl = m_PluginList.values();//TODO FIX ME to type
    foreach( QPluginFabrique* pFab, listPl )
    {
        if( pFab )
        {
            plugin_desc.append( pFab->getDescription() );
        }
    }

    return plugin_desc;
}


QObject* QPluginList::cretate_plugin_object( PluginDescription &desc , QObject *parent )
{

    QObject* object = NULL;
    QList<QPluginFabrique*> listPl = m_PluginList.values();//TODO FIX ME to type
    foreach( QPluginFabrique* pFab, listPl )
    {
        if(  PluginDescription::THE_SAME == pFab->getDescription( ).compare(desc) )
        {
            object = pFab->cretate_plugin_object( desc.type(), parent );
            if( object )
            {
              break;
            }
        }
    }

    return object;
}

