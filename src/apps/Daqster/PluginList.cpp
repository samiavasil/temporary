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
    connect(ui->availablePlugins,SIGNAL(itemSelectionChanged ()),this, SLOT(listSelectionChanged()));
}

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
                if( loader->load() ){
                    m_PluginList.insert( fileName, loader );
                }
                if( loader->unload() ){
                if( loader->load() )
                  plugin =  loader->instance();
                }
            }
        }
    }
   populatePluginList();
}

void QPluginList::populatePluginList(){
    QObject *plugin;
    FrameWorkInterface *frame;
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");

    ui->availablePlugins->setColumnCount(3);

    QMapIterator<QString,QPluginLoader* > loader(m_PluginList);
    while ( loader.hasNext() ) {
        loader.next();
        qDebug() << loader.key() << ": " << loader.value() << endl;
        QPluginLoader* pluginLoader = loader.value();
        if( true == pluginLoader->load() ){
            plugin = pluginLoader->instance();
            frame = qobject_cast<FrameWorkInterface *>(plugin);
            if( frame ){
                ui->availablePlugins->insertRow(0);
                QTableWidgetItem *item = new QTableWidgetItem(frame->name());
                if( !frame->icon().isNull() ){
                    QIcon icon = frame->icon();
                    item->setIcon( icon );
                    setWindowIcon(icon);
                }
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 0, item );

                item = new QTableWidgetItem(frame->category());
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 1, item );

                item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
                item->setCheckState ( Qt::Checked );
                ui->availablePlugins->setItem( 0, 2, item );
            }
            //m_PluginMap.insert();
        }

    }
    /*
    QPluginLoader* loader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName));
    if( 0 != loader ){
        QObject *plugin = loader->instance();
        if( plugin ){
            FrameWorkInterface *frame = qobject_cast<FrameWorkInterface *>(plugin);
            if( frame ){
                ui->availablePlugins->insertRow(0);
                QTableWidgetItem *item = new QTableWidgetItem(frame->name());
                if( !frame->icon().isNull() ){
                    QIcon icon = frame->icon();
                    item->setIcon( icon );
                    setWindowIcon(icon);
                }
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 0, item );

                item = new QTableWidgetItem(frame->category());
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->availablePlugins->setItem( 0, 1, item );

                item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
                item->setCheckState ( Qt::Checked );
                ui->availablePlugins->setItem( 0, 2, item );
                //m_PluginMap.insert();
            }
            m_PluginList.insert( fileName, loader );
        }
        //loader->unload();
    }
    */
}

void QPluginList::listSelectionChanged(){
    qDebug()<<"Curent Row"<<ui->availablePlugins->currentRow();
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
