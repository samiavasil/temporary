#include "PluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QDir>
#include<QDebug>
#include "qt/QFrameWork.h"


//class QMyTableWidgetItem:public QTableWidgetItem{
//public:
//    QMyTableWidgetItem( const QString &fileName,QObject *parent = 0):QTableWidgetItem ( fileName  ){
//        qDebug("CREATE QMyTableWidgetItem");
//    }
//    ~QMyTableWidgetItem( ){
//        qDebug("DELETE QMyTableWidgetItem");
//    }
//};
//#define QTableWidgetItem QMyTableWidgetItem





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
    //ui->pluginList->clear();
    delete ui;
}


void QPluginList::readPluginsDir( ){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    /*
    if( m_PluginList.count() ){
        QMapIterator<QString,QPluginLoaderExt* > loader(m_PluginList);
        while( loader.hasNext() ){
            loader.next();
            if( loader.value() && loader.value()->instance() ){
                if( loader.value()->unload() ){
                    qDebug()<<"Suxesfully unload before delete"<<loader.value()->fileName();
                }
            }
            delete (loader.value());
        }
        m_PluginList.clear();
    }
*/
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        fileName = pluginsDir.absoluteFilePath(fileName);
        if(  false == m_PluginList.contains( fileName ) ){
            plugin_descriptor* desc = new plugin_descriptor(fileName.toUtf8().data());
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
    QMapIterator<QString,plugin_descriptor* > plugin_list(m_PluginList);
    while ( plugin_list.hasNext() ) {
        plugin_list.next();
        plugin_descriptor* desc = plugin_list.value();
        if( desc ){
            qDebug() <<  desc;
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
           m_PluginList[item_location->text()]->enable( true );
       }
       else{
           m_PluginList[item_location->text()]->enable( false );
       }
    }

#if 0
    if( 0 <= row ) {
        QMap<QString,plugin_descriptor* >::iterator plugin_list = m_PluginList.begin();
        qDebug()<<"Curent Row"<<row;

        if(  Qt::Checked == ui->availablePlugins->item(row,2)->checkState() ){
            if( NULL != (plugin_list+row).value() ){
                qDebug()<<"Hm..Someting Wrogng!!! Unloaded plugin but not NULL pointer";
            }
            QPluginLoaderExt* plLoader = new QPluginLoaderExt((loader+row).key());
            if( plLoader ){
                if( plLoader->instance() ){
                    qDebug()<<"Suxesfully load "<<plLoader->fileName();
                    (loader+row).value()=plLoader;
                }
                else{
                    qDebug()<<"Can't create instance - reload list ' "<<plLoader->fileName();
                    emit reload();
                }
            }
        }
        else{

            if( NULL != (loader+row).value() ){
                delete (loader+row).value()->instance();
                if( (loader+row).value()->unload() ){
                    qDebug()<<"Suxesfully unload "<<(loader+row).value()->fileName();
                }
                else{
                    qDebug()<<"Can't create instance - reload list ' "<< (loader+row).value()->fileName();
                    emit reload();
                }
                delete (loader+row).value();
                (loader+row).value()=NULL;
            }
        }
    }
#endif
}

void QPluginList::reloadPlugins( ){
    qDebug("Reload List");
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

QList<QPluginLoaderExt*>  QPluginList::getAllActivePlugins( InterfaceType_t type ){
    reloadPlugins();
    type = type;

}
