#include "PluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QDir>
#include "qt/QFrameWork.h"
#include <QMdiArea>

class QPluginLoaderMy:public QPluginLoader{
public:
    QPluginLoaderMy( const QString &fileName,QObject *parent = 0):QPluginLoader ( fileName,parent ){
        DEBUG("CREATE QPluginLoaderMy");
    }
    ~QPluginLoaderMy( ){
        DEBUG("DELETE QPluginLoaderMy");
    }
};


QPluginList::QPluginList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginList)
{
    ui->setupUi(this);
    readPluginsDir();
    //populatePluginList();
    ui->availablePlugins->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->availablePlugins->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->availablePlugins,SIGNAL(itemChanged(QTableWidgetItem*) ),this, SLOT(listSelectionChanged(QTableWidgetItem*)));
}
//itemClicked
QPluginList::~QPluginList()
{
    //ui->pluginList->clear();
    delete ui;
}

#include <QMdiSubWindow>
#include<QDebug>

void QPluginList::readPluginsDir( ){
    QDir pluginsDir(qApp->applicationDirPath());
    QObject *plugin;
    pluginsDir.cd("plugins");
    ui->availablePlugins->setColumnCount(3);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        if(  false == m_PluginList.contains( fileName ) ){
            QPluginLoader* loader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName));
            if( 0 != loader ){
                plugin =  loader->instance();
                if( 0 != plugin ){
                    m_PluginList.insert( pluginsDir.absoluteFilePath(fileName), loader );
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
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    ui->availablePlugins->setColumnCount(3);

    QMapIterator<QString,QPluginLoader* > loader(m_PluginList);
    while ( loader.hasNext() ) {
        loader.next();
        qDebug() << loader.key() << ": " << loader.value() << endl;
        QPluginLoader* pluginLoader = loader.value();
        if( true == pluginLoader->load() ){
            QObject *object = pluginLoader->instance();
            plugin = dynamic_cast<plugin_interface *>(object);//qobject_cast
            if( plugin ){
                ui->availablePlugins->insertRow(0);
                QTableWidgetItem *item = new QTableWidgetItem(plugin->name());
                if( !plugin->icon().isNull() ){
                    QIcon icon = plugin->icon();
                    item->setIcon( icon );
                }
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 0, item );

                item = new QTableWidgetItem(plugin->category());
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 1, item );

                item = new QTableWidgetItem( pluginLoader->fileName() );
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
                item->setCheckState ( Qt::Checked );
                ui->availablePlugins->setItem( 0, 2, item );
                object->deleteLater();
            }
            //m_PluginMap.insert();
        }

    }
}

void QPluginList::listSelectionChanged( QTableWidgetItem* item ){
    int row = ui->availablePlugins->currentRow();
    QMap<QString,QPluginLoader* >::iterator loader = m_PluginList.begin();
    qDebug()<<"Curent Row"<<row;

        if(  Qt::Checked == ui->availablePlugins->item(row,2)->checkState() ){
            if( NULL != (loader+row).value() ){
                qDebug()<<"Hm..Someting Wrogng!!! Unloaded plugin but not NULL pointer";
            }
            QPluginLoader* plLoader = new QPluginLoader((loader+row).key());
            if( true == plLoader->load() ){
                qDebug()<<"Suxxesully load "<<plLoader->fileName();
                (loader+row).value()=plLoader;
            }
        }
        else{

            if( NULL != (loader+row).value() ){
                if( (loader+row).value()->unload() ){
                    qDebug()<<"Suxxesully unload "<<(loader+row).value()->fileName();
                }
                delete (loader+row).value();
                (loader+row).value()=NULL;
            }
        }

    //m_PluginList[ui->availablePlugins->currentRow()]->instance();
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
