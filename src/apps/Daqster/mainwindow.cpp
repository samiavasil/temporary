#include "mainwindow.h"
#include "qt/interfaces.h"

#include"qt/QFrameWork.h"
#include<QMdiSubWindow>
#include<QMouseEvent>

#include"ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, true );
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
    if( ui ){
        delete ui;
    }
}


void MainWindow::onUndoAvailable()
{
    //emit undoAvailable(_designer->core()->formWindowManager()->actionUndo()->isEnabled());
}

void MainWindow::onRedoAvailable()
{
    //emit redoAvailable(_designer->core()->formWindowManager()->actionRedo()->isEnabled());
}

void MainWindow::onCopyAvailable()
{
    //emit copyAvailable(_designer->core()->formWindowManager()->actionCopy()->isEnabled());
}

void MainWindow::onPasteAvailable()
{
    //emit pasteAvailable(_designer->core()->formWindowManager()->actionPaste()->isEnabled());
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
    QPluginList::Instance()->configurePlugins();
   // if( QDialog::Accepted == QPluginList::Instance()->exec() )
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
    QList<PluginDescription> list = QPluginList::Instance()->getAllPlugins( QpluginFilter( UNDEFINED ) );
    for( int i = 0; i < list.count(); i++ ){
        if( FRAME_WORK == list[i].type() )
        {
          QObject* obj;
          obj = QPluginList::Instance()->cretate_plugin_object( list[i] , this );
          if( !obj )
              continue;
          QFrameWork* fw = dynamic_cast<QFrameWork*>(obj);
          if(fw)
          {
             fw->Create();
             //fw->setCreator(NULL);
             QWidget* wd =  fw->getFrameWorkWindow();
             static int b;
             if( wd && (b%2) )
             {
                 ui->mdiArea->addSubWindow(wd);
                 wd->show();//DELL ME
             }
             b++;
          }

        }

    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
        /*if (maybeSave()) {
            writeSettings();
            event->accept();
        } else {
            event->ignore();
        }*/
    if( 1 ){//TODO
        event->accept();
        foreach (QWidget *widget, QApplication::topLevelWidgets()) {
          widget->close();
        }
    }
}
