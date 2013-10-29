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
//ui->PlotWidget->addSubWindow(tool,Qt::Tool);
    //ui->PlotWidget->addWidget(tool);
    QObject::connect(combo, SIGNAL(currentIndexChanged(int)) , this, SLOT(on_mdi_change_view_mode(int)));
}

QFraFrameWork::~QFraFrameWork(){

}

void QFraFrameWork::on_mdi_change_view_mode(int id )
{
    ui->PlotWidget->setViewMode( (QMdiArea::ViewMode)id );
    ui->PlotWidget->setTabPosition( QTabWidget::South );
}

#include <QMdiSubWindow>
void QFraFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{
    //ui->verticalLayout->addWidget(widget);
    //ui->PlotWidget->layout()->addWidget(widget);
   QMdiSubWindow * mdi_win =  ui->PlotWidget->addSubWindow(widget);
    //ui->PlotWidget->setVisible(true);
    //ui->PlotWidget->setCurrentIndex(2);

    QAction* act = new QAction("Tuk she ti go tura", mdi_win );
    act->setMenuRole(QAction::ApplicationSpecificRole);
    mdi_win->insertAction(0 , act );
    mdi_win->setContextMenuPolicy ( Qt::ActionsContextMenu );

    list.append(widget);

    //ui->PlotWidget->removeSubWindow( widget );
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

