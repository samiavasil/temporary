#include "QPluginSelectionView.h"
#include "ui_QPluginSelectionView.h"
#include "qt/QPluginList.h"


QPluginSelectionView::QPluginSelectionView(QWidget *parent, const QPluginFilter &filter, const cfgViewTypeT &viewType) :
    QWidget(parent),
    ui(new Ui::QPluginSelectionView),m_wd(this, filter, viewType)
{
    ui->setupUi(this);

    ui->verticalLayout->insertWidget( 0, &m_wd );
    adjustSize();

    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,&m_wd, SLOT(reloadPLuginList()) ) ;
    connect( &m_wd,SIGNAL(selectedPluginChanged(PluginDescription)),this, SLOT(selectedPluginChanged(PluginDescription)) );
    connect(ui->Ok,SIGNAL(clicked()),this,SIGNAL(ok_selected()));
    connect(ui->Cancel,SIGNAL(clicked()),this,SIGNAL(cancel_selected()));
}

QPluginSelectionView::~QPluginSelectionView()
{
    delete ui;
}


void QPluginSelectionView::selectedPluginChanged(const PluginDescription& desc){
    ui->textEdit->setText( desc.description() );//TODO fill more
}

const PluginDescription QPluginSelectionView::getSelectedPlugin(){
    return m_wd.getSelectedPlugin();
}
