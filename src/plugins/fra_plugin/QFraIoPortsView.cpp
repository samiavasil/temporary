#include "base/global.h"
#include "QFraIoPortsView.h"
#include "ui_QFraIoPortsView.h"
#include "qt/QPortIO.h"
#include "qt/QPluginList.h"

QFraIoPortsView::QFraIoPortsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QfraIoPortsView)
{
    mCurrentIo = NULL;
    ui->setupUi(this);

}

QFraIoPortsView::~QFraIoPortsView()
{
    delete ui;
    foreach( PluginDescription* pDesc, mIoPorts )
    {
       delete pDesc;
    }
    mIoPorts.clear();
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

void QFraIoPortsView::addToList( PluginDescription desc )
{
    ui->IoList->blockSignals( true );
    mIoPorts.append( new PluginDescription( desc ) );
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
            int idx = ui->IoList->count()-1;
            QListWidgetItem* ds = ui->IoList->takeItem( idx );
            if( ds )
            {
                delete ds;
            }
            PluginDescription* desc = mIoPorts.takeAt( idx );
            if( desc )
            {
                delete desc;
            }
        }
    }
    ui->IoList->blockSignals( false );
}

QPortIO* QFraIoPortsView::getCurentIO(  )
{
   return mCurrentIo;
}

void QFraIoPortsView::on_IoList_currentRowChanged( int currentRow )
{
    mCurrentIo->deleteLater();
    mCurrentIo = NULL;
    PluginDescription* desc = mIoPorts.value( currentRow, NULL );
    if( desc )
    {
        mCurrentIo = dynamic_cast<QPortIO*>(QPluginList::Instance()->cretate_plugin_object( *desc, this ));
        if( NULL != mCurrentIo )
        {
            mCurrentIo->showPortConfiguration( ui->ioCtrlWidget );
        }
    }
}
