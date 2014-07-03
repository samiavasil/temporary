#include "base/global.h"
#include "QPortsIoView.h"
#include "ui_QPortsIoView.h"
#include "qt/QPortIO.h"
#include "qt/QPluginList.h"
#include "qt/QPluginListWidget.h"


QPortsIoView::QPortsIoView(QWidget *parent) : QWidget(parent), ui( new Ui::QPortsIoView )
{
    cfgViewTypeT view;
    view.hideDisabled(true).name(true).icon(true);
    QPluginListWidget* wd = new QPluginListWidget( this, PORT_IO ,  view );
    mCurrentIo = NULL;
    ui->setupUi(this);
    ui->splitter->insertWidget( 0, wd );
    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,wd, SLOT(reloadPLuginList()) );
    connect( wd,SIGNAL(selectedPluginChanged(PluginDescription)),this, SLOT(selectedPluginChanged(PluginDescription)) );
}

QPortsIoView::~QPortsIoView()
{
    delete ui;
    mIoPorts.clear();
    if( mCurrentIo ){
        mCurrentIo->deleteLater();
    }

}


QPortIO* QPortsIoView::getCurentIO(  )
{
   return mCurrentIo;
}


void QPortsIoView::selectedPluginChanged( const PluginDescription &desc )
{
    if( mCurrentIo ){
        mCurrentIo->deleteLater();
        mCurrentIo = NULL;
    }
    mCurrentIo = dynamic_cast<QPortIO*>(QPluginList::Instance()->cretate_plugin_object( desc, this ));
    if( NULL != mCurrentIo )
    {
        mCurrentIo->showPortConfiguration( ui->ioCtrlWidget );
    }

}
