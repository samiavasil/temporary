#include "QFraFrameWork.h"
#include <ui_qfra_frame_work_view.h>
#include<QComboBox>
#include<QToolBar>
#include<QVBoxLayout>

QFraFrameWork::QFraFrameWork(QCreator * creator  , QWidget * parent ):
    QFrameWork( creator , parent ),ui(new Ui::QFraFrameWorkView)
{
    ui->setupUi(this);
    QToolBar* tool  = new QToolBar( NULL );
    QComboBox* combo = new QComboBox(tool);
    //QVBoxLayout * lay = new QVBoxLayout();
    tool->setAllowedAreas( Qt::AllToolBarAreas );
    tool->setPalette(QPalette(QColor(99,99,99)));
    combo->addItem("QMdiArea::SubWindowView");
    combo->addItem("QMdiArea::TabbedView");
    tool->addWidget( combo );
    tool->setFloatable( true );
    tool->setMovable( true );
    ui->plotLayout->insertWidget( 0, tool );
    //ui->PlotWidgetMDI->setTabShape( QTabWidget::Triangular );
    ui->PlotWidgetMDI->setTabsClosable( true );
    ui->PlotWidgetMDI->setTabsMovable( true );
   // ui->PlotWidgetMDI->setDocumentMode( true );
//ui->PlotWidgetMDI->addSubWindow(tool,Qt::Tool);
    //ui->PlotWidgetMDI->addWidget(tool);
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)) , this, SLOT(on_mdi_change_view_mode(int)));
}

QFraFrameWork::~QFraFrameWork(){

}

void QFraFrameWork::on_mdi_change_view_mode(int id )
{
    ui->PlotWidgetMDI->setViewMode( (QMdiArea::ViewMode)id );
    ui->PlotWidgetMDI->setTabPosition( QTabWidget::South );
}

#include <QMdiSubWindow>
void QFraFrameWork::on_detach_MDI_window( bool togg )
{
    QAction*act = dynamic_cast<QAction* >( QObject::sender() );
    if( act )
    {
        QMdiSubWindow* win = dynamic_cast<QMdiSubWindow* >( act->parentWidget() );
        if( win )
        {
            if( togg )
            {
                ui->PlotWidgetMDI->removeSubWindow( win );

            }
            else
            {
                Q_ASSERT( win->parent() == NULL );
                ui->PlotWidgetMDI->addSubWindow( win );
            }
            win->setVisible(true);
        }
    }
}



void QFraFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{
    //ui->verticalLayout->addWidget(widget);
    //ui->PlotWidgetMDI->layout()->addWidget(widget);
    QMdiSubWindow * mdi_win =  ui->PlotWidgetMDI->addSubWindow( widget );
    //ui->PlotWidgetMDI->setVisible(true);
    //ui->PlotWidgetMDI->setCurrentIndex(2);

    QAction* act = new QAction("Tuk she ti go tura", mdi_win );
    act->setCheckable(true);
    act->setChecked(false);
    act->setMenuRole(QAction::ApplicationSpecificRole);
    mdi_win->insertAction(0 , act );
    mdi_win->setContextMenuPolicy ( Qt::ActionsContextMenu );
    QObject::connect( act, SIGNAL(triggered(bool)), this, SLOT(on_detach_MDI_window(bool)) );
//mdi_win->setParent(NULL);
//mdi_win->setVisible(true);
    list.append(widget);

    //ui->PlotWidgetMDI->removeSubWindow( widget );
    //widget->setVisible(true);
}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
     ui->PortIoConfig->addWidget(widget);
}

void QFraFrameWork::on_StartButton_clicked()
{
    static bool b;
    b=!b;
    for( int i = 0; i< list.count(); i++ )//TODO DELL ME
     list[i]->setProperty( "TestPropety", b );
}

