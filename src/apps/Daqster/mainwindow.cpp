#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qt/interfaces.h"
#include"qt/QFrameWork.h"
#include<QMdiSubWindow>
#include<QMouseEvent>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
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
   // createQTDesignerWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::onUndoAvailable()
{
  //  emit undoAvailable(_designer->core()->formWindowManager()->actionUndo()->isEnabled());
}

void MainWindow::onRedoAvailable()
{
 //   emit redoAvailable(_designer->core()->formWindowManager()->actionRedo()->isEnabled());
}

void MainWindow::onCopyAvailable()
{
  //  emit copyAvailable(_designer->core()->formWindowManager()->actionCopy()->isEnabled());
}

void MainWindow::onPasteAvailable()
{
  //  emit pasteAvailable(_designer->core()->formWindowManager()->actionPaste()->isEnabled());
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
          QWidget* wd = new QWidget(this);
          ui->mdiArea->addSubWindow(wd);
          wd->show();//DELL ME
          obj = QPluginList::Instance()->cretate_plugin_object( list[i] , wd );
          if( !obj )
              continue;
          QFrameWork* fw = dynamic_cast<QFrameWork*>(obj);
          if(fw)
          {
             fw->Create();
             fw->show();
          }
          if( obj->isWidgetType() )
          {
                QWidget* wd = (QWidget*)obj;
//               ui->mdiArea->addSubWindow(wd);
                wd->show();//DELL ME
          }
        }

    }

}
