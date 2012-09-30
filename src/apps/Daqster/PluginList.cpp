#include "PluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QDir>
#include<QDebug>



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
    QObject *plugin;
    pluginsDir.cd("plugins");
    if( m_PluginList.count() ){
        QMapIterator<QString,QPluginLoader* > loader(m_PluginList);
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
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        fileName = pluginsDir.absoluteFilePath(fileName);
        if(  false == m_PluginList.contains( fileName ) ){
            QPluginLoader* loader = new QPluginLoader(fileName);
            if( 0 != loader ){
                plugin =  loader->instance();
                if( 0 != plugin ){
                    qDebug() << fileName << ":vvv: " << loader << endl;
                    m_PluginList.insert( fileName, loader );
                    plugin->deleteLater();
                }
                else{
                    qDebug()<<"Can't load plugin from file " << loader->fileName();
                    loader->deleteLater();
                }
            }
            else{
                qDebug()<<"Can't create plugin loader from file " << pluginsDir.absoluteFilePath(fileName);
            }
        }
    }
    populatePluginList();
}

void QPluginList::populatePluginList(){
    plugin_interface *plugin;
    int i =0;
    ui->availablePlugins->clear();
    ui->availablePlugins->setRowCount(0);
    ui->availablePlugins->setColumnCount(3);
    QMapIterator<QString,QPluginLoader* > loader(m_PluginList);
    while ( loader.hasNext() ) {
        loader.next();
        qDebug() << loader.key() << ": " << loader.value() << endl;
        QPluginLoader* pluginLoader = loader.value();
        if( true == pluginLoader->load() ){
            QObject *object = pluginLoader->instance();
            plugin = dynamic_cast<plugin_interface *>(qobject_cast<FrameWorkInterface*>(object));//qobject_cast
            if( plugin ){
                ui->availablePlugins->insertRow( i );
                QTableWidgetItem *item = new QTableWidgetItem(plugin->name());
                if( !plugin->icon().isNull() ){
                    QIcon icon = plugin->icon();
                    item->setIcon( icon );
                }
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( i, 0, item );

                item = new QTableWidgetItem(plugin->category());
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( i, 1, item );

                item = new QTableWidgetItem( pluginLoader->fileName() );
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
                item->setCheckState ( Qt::Checked );
                ui->availablePlugins->setItem( i, 2, item );
                object->deleteLater();
                i++;
            }
        }
    }
}

void QPluginList::listSelectionChanged( QTableWidgetItem* item ){
    int row = ui->availablePlugins->row(item);
    if( 0 <= row ) {
        QMap<QString,QPluginLoader* >::iterator loader = m_PluginList.begin();
        qDebug()<<"Curent Row"<<row;

        if(  Qt::Checked == ui->availablePlugins->item(row,2)->checkState() ){
            if( NULL != (loader+row).value() ){
                qDebug()<<"Hm..Someting Wrogng!!! Unloaded plugin but not NULL pointer";
            }
            QPluginLoader* plLoader = new QPluginLoader((loader+row).key());
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
