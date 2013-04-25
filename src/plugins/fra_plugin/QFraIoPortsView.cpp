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

void QFraIoPortsView::addToList( PluginDescription desc )
{
    mIoPorts.append( new PluginDescription( desc ) );
    ui->IoList->addItem( desc.name() );
    if( ui->IoList->count() == 1 || mCurrentIo == NULL )
    {
        mCurrentIo = dynamic_cast<QPortIO*>(QPluginList::Instance()->cretate_plugin_object( desc, this ));
        if( NULL != mCurrentIo )
        {
            QWidget* w = new QWidget();
            ui->IoCtrlLayout->addWidget( w );
            mCurrentIo->showPortConfiguration( w );
            ui->IoList->setCurrentRow(0);
         }
        else
        {
            QListWidgetItem* ds = ui->IoList->takeItem( ui->IoList->count()-1 );
            if( ds )
            {
                delete ds;
            }
        }
    }
}

 QPortIO* QFraIoPortsView::getCurentIO(  )
{
   return mCurrentIo;
}
