#include "qt/QFrameWork.h"
#include "qt/QCreator.h"
#include<qevent.h>
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

QFrameWork::QFrameWork(QCreator * creator, QObject * parent):QObject(parent),CFrameWork(creator){
  DEBUG << "Create QFrameWork";
   m_FwWin = new QFwWidget();
   QObject::connect(m_FwWin, SIGNAL(destroyFW()) , this, SLOT(deleteLater()));
   m_FwWin->show();
}

QFrameWork::~QFrameWork() {
  DEBUG << "Destroy QFrameWork";
  if( m_FwWin ){
    //  m_FwWin->deleteLater();//Deletedin close event see gore
      m_FwWin = NULL;
  }
  emit fwDestroy();
}

//bool QFrameWork::Create() {
//  if( m_creator )
//    return m_creator->Create( this );
//  else
//    return true;
//}


