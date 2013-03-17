#include "qt/QPluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QDir>
#include "qt/QFrameWork.h"

QPluginList* QPluginList::m_This = NULL;
QMap< QString, QPluginDescriptor*  > QPluginList::m_PluginList;
QPluginList* QPluginList::Instance()
{
    qDebug() << "INPUT" << m_This;
        if( NULL == m_This )
        {
            m_This = new QPluginList();
        }

    qDebug() << "OUTPUT" << m_This;
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
    QMapIterator<QString,QPluginDescriptor* > plugin_list(m_PluginList);
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
            QPluginDescriptor* desc = new QPluginDescriptor(fileName.toUtf8().data());
            if( 0 != desc ){
                m_PluginList.insert( fileName, desc );
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
    QMapIterator<QString,QPluginDescriptor* > plugin_list(m_PluginList);
    while ( plugin_list.hasNext() ) {
        plugin_list.next();
        QPluginDescriptor* desc = plugin_list.value();
        if( desc ){
            DEBUG() <<  desc;
            ui->availablePlugins->insertRow( i );
            QTableWidgetItem *item = new QTableWidgetItem(desc->name());
            if( !desc->icon().isNull() ){
                QIcon icon = desc->icon();
                item->setIcon( icon );
            }
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->availablePlugins->setItem( i, 0, item );

            item = new QTableWidgetItem(desc->category());
            item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->availablePlugins->setItem( i, 1, item );

            item = new QTableWidgetItem( desc->location() );
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
    DEBUG("Reload List");
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

QList<QPluginDescriptor *> QPluginList::getAllActivePlugins( InterfaceType_t type ){
    reloadPlugins();
    type = type;
    return  m_PluginList.values();
}
