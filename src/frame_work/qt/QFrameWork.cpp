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

QFrameWork::QFrameWork(QCreator * creator, QObject * parent):QObject(parent){
    m_creator = creator;
    DEBUG << "Create QFrameWork";
    m_FwWin = new QFwWidget();
    QObject::connect(m_FwWin, SIGNAL(destroyFW()) , this, SLOT(deleteLater()));
    m_FwWin->show();
}

QFrameWork::~QFrameWork() {
    DEBUG << "Destroy QFrameWork";
    if( m_creator )
    {
        delete m_creator;
        m_creator = 0;
    }
    if( m_FwWin ){
        //  m_FwWin->deleteLater();//TODO: Check this - Deletedin close event see gore
        m_FwWin = NULL;
    }
    emit fwDestroy();
}

bool QFrameWork::Create() {
  bool bRet  = true;
  if( m_creator )
      bRet = m_creator->Create( this );
  return bRet;
}

/**
 * TODO: TBD
 */
void QFrameWork::setCreator(QCreator *creator) {
  if( m_creator )
  {
    m_creator->Free();
    delete m_creator;
  }
  m_creator = creator;
  Create();
}

QMainWindow *QFrameWork::getFrameWorkWindow(){
    return m_FwWin;
}


