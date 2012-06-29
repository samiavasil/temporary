#include "PluginList.h"
#include "ui_pluginlist.h"
#include "interfaces.h"
#include <QPluginLoader>
#include <QDir>
#include "QFrameWork.h"

PluginList::PluginList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginList)
{
    ui->setupUi(this);
    populatePluginList();
}

PluginList::~PluginList()
{
    delete ui;
}

void PluginList::populatePluginList(){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    ui->pluginList->setColumnCount(3);
    ui->pluginList->setRowCount(0);

    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        ui->pluginList->insertRow( ui->pluginList->rowCount() );
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if( plugin ){
            FrameWorkInterface *frame = qobject_cast<FrameWorkInterface *>(plugin);
            if( frame ){
                ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 0,new QTableWidgetItem( frame->name()) );
                ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->addItem(QString("Plugin: %1   PluginFileName: %2").arg(frame->name()).arg(fileName));
            }
        }
        loader.unload();
    }
    //ui->pluginList->setCurrentRow(0);
}

void PluginList::on_okButton_clicked()
{
    close();
    setResult( Accepted );
}

void PluginList::on_cancelButton_clicked()
{
    close();
    setResult( Rejected );
}
