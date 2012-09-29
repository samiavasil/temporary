#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "interfaces.h"
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),m_PluginList(this)
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include<QDebug>
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


    if( QDialog::Accepted == m_PluginList.exec() )
    {
        //DEBUG("%d", pList.exec());
    }
}

void MainWindow::on_actionFullScreen_triggered(bool checked)
{
    static QMdiSubWindow* old;
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
