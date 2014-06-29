#include "QFraFrameWork.h"
#include <ui_qfra_frame_work_view.h>
#include<qevent.h>
#include<QComboBox>
#include<QToolBar>
#include<QVBoxLayout>
#include <QMdiSubWindow>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFwWidget::QFwWidget( QWidget *parent, Qt::WindowFlags f ):QMainWindow( parent,f ){

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

 //   QVBoxLayout *layout = new QVBoxLayout;
    m_FwWin = new QFwWidget();

    QToolBar* tool  = new QToolBar( m_FwWin );
    QComboBox* combo = new QComboBox(tool);
    QWidget*w = new QWidget(m_FwWin);


    ui->setupUi(w);

    m_FwWin->setCentralWidget(w);
    tool->setMovable(1);
    tool->setFloatable(1);
    //QVBoxLayout * lay = new QVBoxLayout();
    tool->setAllowedAreas( Qt::TopToolBarArea | Qt::BottomToolBarArea );
    tool->setPalette(QPalette(QColor(99,99,99)));
    combo->addItem("QMdiArea::SubWindowView");
    combo->addItem("QMdiArea::TabbedView");
    QAction *actionView;
    actionView = new QAction(QIcon(QString::fromUtf8(":/fra/icons/FrameWork.png")),"AddView", this);
    connect(actionView, SIGNAL(triggered()), this, SLOT(newView()));
    tool->addAction( actionView );


    tool->addSeparator();
    tool->addWidget( combo );
    tool->setFloatable( true );
    tool->setMovable( true );
    m_FwWin->addToolBar(Qt::TopToolBarArea, tool);
    ui->PlotWidgetMDI->setTabsClosable( true );
    ui->PlotWidgetMDI->setTabsMovable( true );

    QObject::connect(combo, SIGNAL(currentIndexChanged(int)) , this, SLOT(on_mdi_change_view_mode(int)));
    QObject::connect(m_FwWin, SIGNAL(destroyFW()) , this, SLOT(deleteLater()));

}

QFraFrameWork::~QFraFrameWork(){
    if( m_FwWin ){
        m_FwWin = NULL;
    }
    foreach (QObject* obj, nonAutoCleanList) {
        if( obj ){
            QString b = obj->property( "WinType").toString();
            if( !b.compare("FlyingWindow") ){
                delete obj;
                nonAutoCleanList.removeAll(obj);
            }
        }
    }
}

void QFraFrameWork::on_mdi_change_view_mode(int id )
{
    ui->PlotWidgetMDI->setViewMode( (QMdiArea::ViewMode)id );
    ui->PlotWidgetMDI->setTabPosition( QTabWidget::South );
}


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
                win->setProperty( "WinType", QString("FlyingWindow") );
                nonAutoCleanList.append(win);
                DEBUG<< "Append: "<< win;
                connect(win,SIGNAL(destroyed(QObject*)),this,SLOT(dbg(QObject*)));

            }
            else
            {
                Q_ASSERT( win->parent() == NULL );
                ui->PlotWidgetMDI->addSubWindow( win );
                nonAutoCleanList.removeAll(win);
            }
            win->adjustSize();
            win->setVisible(true);
        }
    }
}
void QFraFrameWork::dbg(QObject* obj){
    DEBUG<<"Destroy: " << obj;
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

}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
     ui->PortIoConfig->addWidget(widget);
}

void QFraFrameWork::on_StartButton_clicked()
{
    static bool b;
    b=!b;
    for( int i = 0; i< nonAutoCleanList.count(); i++ )//TODO DELL ME
     nonAutoCleanList[i]->setProperty( "TestPropety", b );
}

QWidget* QFraFrameWork::getFrameWorkWindow(){
    return m_FwWin;
}

#include "qt/QPluginSelectionView.h"
void QFraFrameWork::newView(){

    cfgViewTypeT view;
    view.hideDisabled(true).name(true).icon(true);
    QDialog dlg;
    QPluginSelectionView* vv = new QPluginSelectionView( &dlg, QpluginFilter(DATA_OUT), view );
    dlg.exec();
//QWidget
}
