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


PluginList::PluginList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginList)
{
    ui->setupUi(this);
    populatePluginList();
}

PluginList::~PluginList()
{
    //ui->pluginList->clear();
    delete ui;
}
#include <QMdiSubWindow>
void PluginList::populatePluginList(){
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if( plugin ){
            FrameWorkInterface *frame = qobject_cast<FrameWorkInterface *>(plugin);
            if( frame ){
                ui->activePluginList->addItem( frame->name() );
                //ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->addItem(QString("Plugin: %1   PluginFileName: %2").arg(frame->name()).arg(fileName));
            }
        }
        loader.unload();
    }
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
