#include "QFraFrameWork.h"
#include <ui_qfra_frame_work_view.h>
#include<QComboBox>
#include<QToolBar>
#include<QVBoxLayout>
#include <QMdiSubWindow>
#include "qt/QPluginList.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QFraFrameWork::QFraFrameWork(QCreator * creator  , QObject *parent ):
    QFrameWork( creator , parent ),ui(new Ui::QFraFrameWorkView)
{
    
    //   QVBoxLayout *layout = new QVBoxLayout;

    
    QToolBar* tool  = new QToolBar( m_FwWin );
    QComboBox* combo = new QComboBox(tool);
    QWidget*w = new QWidget(m_FwWin);
    
    ui->setupUi(w);
    
    m_FwWin->setCentralWidget(w);
    tool->setMovable(1);
    tool->setFloatable(1);
    tool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
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



    /**
      TODO - DELL ME - tis is only example how to check signa slot connection signatures!!!!!!!!
    */
    QByteArray theSignal =
            QMetaObject::normalizedSignature(SIGNAL(currentIndexChanged(int)));
    QByteArray theSlot =
            QMetaObject::normalizedSignature(SLOT(on_mdi_change_view_mode(int)) );
    if (QMetaObject::checkConnectArgs(theSignal,
                                      theSlot)){
        QObject::connect(combo, SIGNAL(currentIndexChanged(int)) , this, SLOT(on_mdi_change_view_mode(int)));
    }


}

QFraFrameWork::~QFraFrameWork(){

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
    mdi_win->show();
}

void QFraFrameWork::AddWidgetToControlArrea ( QWidget* widget ){
    if( widget ){
        //TODO:: ADD something real for widgets container
        ui->FraWidget->addTab(widget,widget->windowTitle());
    }
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
    connect( vv, SIGNAL(ok_selected()),&dlg, SLOT(accept()) );
    connect( vv, SIGNAL(cancel_selected()),&dlg, SLOT(reject()) );
    if( QDialog::Accepted == dlg.exec() ){
        PluginDescription des ( vv->getSelectedPlugin() );
        QObject* obj = QPluginList::Instance()->cretate_plugin_object( des , NULL );
        if( obj )
        {
            //dynamic_cast<QWidget*>(obj)->show();
            AddWidgetToDataViewArrea( dynamic_cast<QWidget*>(obj) );
        }
    }
    
}
