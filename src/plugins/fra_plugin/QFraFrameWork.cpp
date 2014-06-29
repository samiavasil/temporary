#include "QFraFrameWork.h"
#include <ui_qfra_frame_work_view.h>
#include<qevent.h>
#include<QComboBox>
#include<QToolBar>
#include<QVBoxLayout>

QFwWidget::QFwWidget( QWidget *parent, Qt::WindowFlags f ):QWidget( parent,f ){

}

QFwWidget::~QFwWidget(){

}

void QFwWidget::closeEvent(QCloseEvent *event)
{
        /*if (maybeSave()) {
            writeSettings();
            event->accept();
        } else {
            event->ignore();
        }*/
    if( event ){//TODO
        event->accept();
        deleteLater();
        emit destroyFW();
    }
}

QFraFrameWork::QFraFrameWork(QCreator * creator  , QObject *parent ):
    QFrameWork( creator , parent ),ui(new Ui::QFraFrameWorkView)
{
    //if( parent && parent->isWidgetType() ){
      //  m_FwWin.setParent( dynamic_cast<QWidget*>(parent) );
    //}
    m_FwWin = new QFwWidget();
    this->setParent( m_FwWin );
    ui->setupUi(m_FwWin);
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

    QObject::connect(combo, SIGNAL(currentIndexChanged(int)) , this, SLOT(on_mdi_change_view_mode(int)));
    QObject::connect(m_FwWin, SIGNAL(destroyFW()) , this, SLOT(deleteLater()));
}

QFraFrameWork::~QFraFrameWork(){
    if( m_FwWin ){
    //    m_FwWin->deleteLater();
        m_FwWin = NULL;
    }
    foreach (QObject* win, listWin) {
        if(win){
            if( win->parent() ){
               win->parent()->deleteLater();
            }
        }
    }
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
                Q_ASSERT( win->parent() == NULL );
            }
            else
            {
                Q_ASSERT( win->parent() == NULL );
                ui->PlotWidgetMDI->addSubWindow( win );
            }
            win->adjustSize();
            win->setVisible(true);
        }
    }
}



void QFraFrameWork::AddWidgetToDataViewArrea( QWidget* widget )
{
    QMdiSubWindow * mdi_win =  ui->PlotWidgetMDI->addSubWindow( widget );
    QAction* act = new QAction("Tuk she ti go tura", mdi_win );
    act->setCheckable(true);
    act->setChecked(false);
    act->setMenuRole(QAction::ApplicationSpecificRole);
    mdi_win->insertAction(0 , act );
    mdi_win->setContextMenuPolicy ( Qt::ActionsContextMenu );
    QObject::connect( act, SIGNAL(triggered(bool)), this, SLOT(on_detach_MDI_window(bool)) );
    mdi_win->adjustSize();
    listWin.append(widget);
}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
     ui->PortIoConfig->addWidget(widget);
}

void QFraFrameWork::on_StartButton_clicked()
{
    static bool b;
    b=!b;
    for( int i = 0; i< listWin.count(); i++ )//TODO DELL ME
     listWin[i]->setProperty( "TestPropety", b );
}

QWidget* QFraFrameWork::getFrameWorkWindow(){
    return m_FwWin;
}
