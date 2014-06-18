#include "base/global.h"
#include "QPortsIoView.h"
#include "ui_QPortsIoView.h"
#include "qt/QPortIO.h"
#include "qt/QPluginList.h"
#include "qt/QPluginListWidged.h"

QPortsIoView::QPortsIoView(QWidget *parent) : QWidget(parent), ui( new Ui::QPortsIoView )
{
    QPluginListWidged* wd = new QPluginListWidged( this,PORT_IO  );
    mCurrentIo = NULL;
    ui->setupUi(this);
    ui->splitter->insertWidget( 0, wd );
    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,this, SLOT(reloadPIOlist()) );
    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,wd, SLOT(reloadPLuginList()) );
    reloadPIOlist();
}

QPortsIoView::~QPortsIoView()
{
    delete ui;
    mIoPorts.clear();
    if( mCurrentIo ){
        mCurrentIo->deleteLater();
    }

}

class gpWidget:public QWidget
{
public:
    gpWidget(QWidget* parent=NULL):QWidget(parent)
    {

    }
    ~gpWidget()
    {
        DEBUG << "destroy  gpWidget"<<endl;
    }
};

void QPortsIoView::addToList( PluginDescription& desc )
{
    ui->IoList->blockSignals( true );
    if( !mIoPorts.contains( desc ) ){
        mIoPorts.append( desc );
        ui->IoList->addItem( desc.name() );
        if( ui->IoList->count() == 1 || mCurrentIo == NULL )
        {
            mCurrentIo = dynamic_cast<QPortIO*>(QPluginList::Instance()->cretate_plugin_object( desc, this ));
            if( NULL != mCurrentIo )
            {

                mCurrentIo->showPortConfiguration( ui->ioCtrlWidget );
                ui->IoList->setCurrentRow(0);
             }
            else
            {
                int idx = ui->IoList->count() - 1;
                QListWidgetItem* ds = ui->IoList->takeItem( idx );
                if( ds )
                {
                    delete ds;
                }
                mIoPorts.removeAt( idx );
            }
        }
    }
    ui->IoList->blockSignals( false );
}

QPortIO* QPortsIoView::getCurentIO(  )
{
   return mCurrentIo;
}

void QPortsIoView::reloadPIOlist(){

    QList<PluginDescription>  list = QPluginList::Instance()->getAllPlugins( QpluginFilter( PORT_IO ) );
    mIoPorts.clear();
    ui->IoList->clear();
    mCurrentIo->deleteLater();

    foreach( PluginDescription desc, list ){
        if( desc.is_enabled() ){
            addToList( desc );
        }
    }
}

void QPortsIoView::on_IoList_currentRowChanged( int currentRow )
{
    mCurrentIo->deleteLater();
    mCurrentIo = NULL;
    PluginDescription desc = mIoPorts.value( currentRow );

    mCurrentIo = dynamic_cast<QPortIO*>(QPluginList::Instance()->cretate_plugin_object( desc, this ));
    if( NULL != mCurrentIo )
    {
        mCurrentIo->showPortConfiguration( ui->ioCtrlWidget );
    }

}
