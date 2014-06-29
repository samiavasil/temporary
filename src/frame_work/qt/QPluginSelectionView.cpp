#include "QPluginSelectionView.h"
#include "ui_QPluginSelectionView.h"
#include "qt/QPluginList.h"


QPluginSelectionView::QPluginSelectionView(QWidget *parent, const QpluginFilter &filter, const cfgViewTypeT &viewType) :
    QWidget(parent),
    ui(new Ui::QPluginSelectionView)
{
    ui->setupUi(this);
    QPluginListWidget* wd = new QPluginListWidget( this, filter, viewType );


    ui->verticalLayout->insertWidget( 0, wd );
    adjustSize();

    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,wd, SLOT(reloadPLuginList()) ) ;
    connect( wd,SIGNAL(selectedPluginChanged(PluginDescription)),this, SLOT(selectedPluginChanged(PluginDescription)) );
}

QPluginSelectionView::~QPluginSelectionView()
{
    delete ui;
}


void QPluginSelectionView::selectedPluginChanged(const PluginDescription& desc){
    ui->textEdit->setText( desc.description() );//TODO fill more
}
