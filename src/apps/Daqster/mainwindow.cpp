#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qt/interfaces.h"
#include"qt/QFrameWork.h"
#include<QMdiSubWindow>
#include<QMouseEvent>

#if 0
void PluginList::populatePluginList(){
    static int a;
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    ui->pluginList->setColumnCount(3);
    ui->pluginList->setRowCount(0);
    static QMdiSubWindow* fw_old;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        ui->pluginList->insertRow( ui->pluginList->rowCount() );
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if( plugin ){
            FrameWorkInterface *frame = qobject_cast<FrameWorkInterface *>(plugin);
            if( frame ){
                ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 0,new QTableWidgetItem( frame->name()) );
                ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->setItem( ui->pluginList->rowCount() - 1, 2,new QTableWidgetItem( fileName ) );
                //ui->pluginList->addItem(QString("Plugin: %1   PluginFileName: %2").arg(frame->name()).arg(fileName));
            }

            QMdiArea* mdi = ((QMdiArea*)parentWidget());
            //mdi->setOption ( QMdiArea::DontMaximizeSubWindowOnActivation, true );
            QList<QMdiSubWindow *> list = mdi->subWindowList( );
            mdi->setTabsMovable(true);
            int len = list.count();

            if( len < 4 ){
                QFrameWork* fw = frame->getFrameWork(NULL);//parentWidget());
                fw->setWindowTitle(QString("Form %1").arg(a));
                //fw->setWindowIcon(QIcon(QString::fromUtf8(":/new/prefix1/icons/radiobutton_on.png")));
                fw_old = mdi->addSubWindow(fw);
#if 0
                QTabBar* tabbar = mdi->findChild<QTabBar*>();
                if( tabbar ){
                    QSize size( 30,30);

                    //   tabbar->setSizePolicy( QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred) );
                    //   tabbar->resize(size);
                    //size = tabbar->iconSize();
                    //size.setHeight(2*size.height());
                    //size.setWidth(2*size.width());
                    tabbar->setIconSize(size);
                    tabbar->setTabIcon( tabbar->count()-1,QIcon(QString::fromUtf8(":/new/prefix1/icons/radiobutton_on.png")));
                }

#endif
                fw->show();

            }
            else
            {
                mdi->closeAllSubWindows();
                /*
                if( (a&1) ){
                    mdi->removeSubWindow(fw_old);
                }
                else
                {
                    mdi->addSubWindow(fw_old);
                }
*/
            }
            a++;


        }

        //TODO  loader.unload();
    }
    //ui->pluginList->setCurrentRow(0);
}

#endif


#include <QtDesigner>

#include <QtDesigner/qdesigner_components.h>
#include <QtDesigner/QDesignerFormEditorInterface>

#include <QDebug>
#include <QFile>
#include <QPluginLoader>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QDir>
#include <QCloseEvent>
#include <QScrollBar>
#include <QTextCodec>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerComponents>
#include <QtDesigner/QDesignerWidgetBoxInterface>
#include <QtDesigner/QDesignerFormEditorPluginInterface>
#include <QtDesigner/QDesignerFormWindowManagerInterface>
#include <QtDesigner/QDesignerObjectInspectorInterface>
#include <QtDesigner/QDesignerPropertyEditorInterface>

#include "internals/qdesigner_integration_p.h"
#include "internals/pluginmanager_p.h"
#include "internals/formwindowbase_p.h"

#include "ui_desinger.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),ui_des(new Ui::Designer)
{
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    addAction(ui->actionNew);
    addAction(ui->actionSave);
    addAction(ui->actionOpen);
    addAction(ui->actionFullScreen);
    addAction(ui->actionHideMainMenu);
    addAction(ui->actionHideToolbar);
    setMouseTracking(true);
    ui->mainToolBar->setMouseTracking(true);
    ui->mdiArea->setMouseTracking(true);
    createQTDesignerWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

class PyNotoIntegration: public qdesigner_internal::QDesignerIntegration
{
public:
    PyNotoIntegration(QDesignerFormEditorInterface *core, QObject *parent = 0):
        qdesigner_internal::QDesignerIntegration(core, parent)
    {
        setSlotNavigationEnabled(true);
    }
};

#if defined( DEST_DIR )
#define DT DEST_DIR
#else
#define DT ""
#endif
#define  TO_STR(z) z

void MainWindow::createQTDesignerWidget()
{

    QWidget* w = new QWidget(this);
     ui->mdiArea->addSubWindow(w);
    ui_des->setupUi(w);
    qDebug()<<"1"<<endl<<endl<<endl;
        QDesignerFormEditorInterface *iface = QDesignerComponents::createFormEditor(this);
        qDebug()<<"2"<<endl<<endl<<endl;
        QDesignerPluginManager* man = iface->pluginManager();
        qDebug()<<"3"<<endl<<endl<<endl;
        QStringList str;
        //str   <<man->pluginPaths();
        str<<"../bin/plugins/";
        man->setPluginPaths(str);

        qDebug()<<man->pluginPaths()<<endl;
        iface->setTopLevel(this);
        QDesignerComponents::createTaskMenu(iface, this);
        QDesignerComponents::initializePlugins( iface );
        QDesignerComponents::initializeResources();

        QDesignerWidgetBoxInterface* wb = QDesignerComponents::createWidgetBox(iface, w);

        for(int i=0; i < wb->categoryCount(); i++ )
            qDebug()<<"Category "<< i << ":  " << wb->category(i).type() << wb->category(i).name()<< endl;
        ui_des->layout->addWidget(wb,0,0);
        iface->setWidgetBox(wb);

        QDesignerObjectInspectorInterface *oi;
        oi = QDesignerComponents::createObjectInspector(iface, w);
        ui_des->layout->addWidget(oi,0,1);
        iface->setObjectInspector(oi);

        QDesignerPropertyEditorInterface *pe = QDesignerComponents::createPropertyEditor(iface, w);
        ui_des->layout->addWidget(pe,0,2);
        iface->setPropertyEditor(pe);

        QDesignerActionEditorInterface *ae = QDesignerComponents::createActionEditor(iface, w);
        ui_des->layout->addWidget((QWidget*)ae,1,0);
        iface->setActionEditor(ae);

        ui_des->layout->addWidget(QDesignerComponents::createSignalSlotEditor(iface, w), 0 , 3 );

        ui_des->layout->addWidget(QDesignerComponents::createResourceEditor(iface, w),1,1);



        //form->addResourceFile (  "/home/vasil/tmp/Appearance.ui");

//        form->setFeatures(QDesignerFormWindowInterface::EditFeature);

//pe->setObject();
        //      iface->
//form->setCurrentTool(1);



        _designer = new PyNotoIntegration(iface, w);
        iface->setIntegration(_designer);

        QList<QObject*> plugins = QPluginLoader::staticInstances();
        plugins += iface->pluginManager()->instances();

        foreach (QObject *plugin, plugins) {
            if (QDesignerFormEditorPluginInterface *formEditorPlugin = qobject_cast<QDesignerFormEditorPluginInterface*>(plugin)) {
                if (!formEditorPlugin->isInitialized()){
                    formEditorPlugin->initialize(iface);
                }
            }
        }

        iface->setIntegration(_designer);
        iface->setObjectInspector(oi);
        iface->setWidgetBox(wb);
        iface->setPropertyEditor(pe);
        iface->setActionEditor(ae);

//        QDesignerFormWindowManagerInterface *formWindowManager = iface->formWindowManager();
//        for (int i=0; i<formWindowManager->formWindowCount(); ++i) {
//            QDesignerFormWindowInterface *formWindow = formWindowManager->formWindow(i);
//            if (formWindow == form)
//                formWindow->editWidgets();
//        }

//        connect(iface->formWindowManager()->actionUndo(), SIGNAL(changed()), SLOT(onUndoAvailable()));
//        connect(iface->formWindowManager()->actionRedo(), SIGNAL(changed()), SLOT(onRedoAvailable()));
//        connect(iface->formWindowManager()->actionCopy(), SIGNAL(changed()), SLOT(onCopyAvailable()));
//        connect(iface->formWindowManager()->actionPaste(), SIGNAL(changed()), SLOT(onPasteAvailable()));
        //iface->setPropertyEditor(QDesignerComponents::createPropertyEditor(iface, w) );
        //iface->setFormManager(QDesignerComponents::createFormEditor(iface, w) );

//form->setCurrentTool(1);
QDesignerFormWindowInterface*  form = iface->formWindowManager()->createFormWindow(0, Qt::Widget );
ui_des->layout->addWidget( form, 1, 3 );
//QFile f("/home/vasil/tmp/Appearance.ui");
//f.open(QIODevice::ReadOnly | QIODevice::Text);
//form->setContents(f.readAll());
//f.close();
form->addResourceFile("/home/vasil/tmp/test.qrc");

form->setMainContainer(new QWidget(w));
//form->setMainContainer(form);
form->setGrid(QPoint(10,10));
//form->setFileName("/home/vasil/tmp/Appearance.ui");
form->show();

form->setCurrentTool(0);
iface->formWindowManager()->setActiveFormWindow(form);

}

void MainWindow::onUndoAvailable()
{
    emit undoAvailable(_designer->core()->formWindowManager()->actionUndo()->isEnabled());
}

void MainWindow::onRedoAvailable()
{
    emit redoAvailable(_designer->core()->formWindowManager()->actionRedo()->isEnabled());
}

void MainWindow::onCopyAvailable()
{
    emit copyAvailable(_designer->core()->formWindowManager()->actionCopy()->isEnabled());
}

void MainWindow::onPasteAvailable()
{
    emit pasteAvailable(_designer->core()->formWindowManager()->actionPaste()->isEnabled());
}

void MainWindow::mouseMoveEvent( QMouseEvent * event ){

    if( event ){
        if( !menuBar()->isVisible() ){
            if( ( 10 >= event->pos().y() ) && ( 10 >= event->pos().x() ) ){
                menuBar()->show();
            }
        }
        else{
            int height = menuBar()->size().height();
            if( ( ui->actionHideMainMenu->isChecked() ) && ( height < event->pos().y() )  ){
                menuBar()->hide();
            }
        }
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::on_actionNew_triggered()
{
    if( QDialog::Accepted == QPluginList::Instance()->exec() )
    {
        //DEBUG("%d", pList.exec());
    }
}

void MainWindow::on_actionFullScreen_triggered(bool checked)
{
    //static QMdiSubWindow* old;
    if( checked ){
        showFullScreen();
    }
    else{
        showNormal();
    }

}

void MainWindow::on_actionHideToolbar_triggered(bool checked)
{
    if( checked ){
        ui->mainToolBar->hide();
        ui->statusBar->hide();
    }
    else{
        ui->mainToolBar->show();
        ui->statusBar->show();
    }
}


void MainWindow::on_actionHideMainMenu_triggered(bool checked)
{
    if( checked ){
        menuBar()->hide();
    }
    else{
        menuBar()->show();
    }
}

void MainWindow::on_actionSave_triggered()
{
    QList<PluginDescription> list = QPluginList::Instance()->getAllActivePlugins( UNDEFINED );
    for( int i = 0; i < list.count(); i++ ){
        if( FRAME_WORK == list[i].type() )
        {
          QObject* obj;
          obj = QPluginList::Instance()->cretate_plugin_object( list[i] , NULL );
          if( !obj )
              continue;
          QFrameWork* fw = dynamic_cast<QFrameWork*>(obj);
          if(fw)
          {
             fw->Create();
          }
          if( obj->isWidgetType() )
          {
              QWidget* wd = (QWidget*)obj;
              ui->mdiArea->addSubWindow(wd);
              wd->show();//DELL ME
          }
        }

    }

}
