#include "PluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QPluginLoader>
#include <QDir>
#include "qt/QFrameWork.h"
#include <QMdiArea>

/*class WMyWI:public QTableWidgetItem{
public:
    WMyWI( const QString &text ):QTableWidgetItem ( text ){
        DEBUG("CREATE WMyWI");
    }
    ~WMyWI( ){
        DEBUG("DELETE WMyWI");
    }
};*/


QPluginList::QPluginList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginList)
{
    ui->setupUi(this);
    populatePluginList();
}

QPluginList::~QPluginList()
{
    //ui->pluginList->clear();
    delete ui;
}
#include <QMdiSubWindow>
#include<QDebug>
void QPluginList::populatePluginList(){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    ui->availablePlugins->setColumnCount(3);
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if( plugin ){
            FrameWorkInterface *frame = qobject_cast<FrameWorkInterface *>(plugin);
            if(0){// frame ){
                ui->availablePlugins->insertRow(0);
                QTableWidgetItem *item = new QTableWidgetItem(frame->name());
                if( !frame->icon().isNull() ){

                    item->setIcon( frame->icon() );
setWindowIcon(frame->icon());
                    QList<QSize> list = frame->icon().availableSizes();
                    qDebug()<<"List Sizes\n";
                    for(int i=0;i<list.count();i++){
                        qDebug()<<list[i];
                    }
                }
                ui->availablePlugins->setItem( 0, 0, item );

                item = new QTableWidgetItem(frame->category());
                ui->availablePlugins->setItem( 0, 1, item );

               // item = new QTableWidgetItem();
                /*frame->description()
                ui->availablePlugins->setItem( 0, 2, item );*/

                //ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->addItem(QString("Plugin: %1   PluginFileName: %2").arg(frame->name()).arg(fileName));
            }
        }
        loader.unload();
    }
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
