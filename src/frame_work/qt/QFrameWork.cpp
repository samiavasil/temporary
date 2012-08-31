
#include "qt/QFrameWork.h"
#include "qt/QFrameWorkElementsFactory.h"

#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"
QFrameWork::QFrameWork(QFrameWorkElementsFactory * factory, QWidget * parent) :CFrameWork( factory){
  if( m_Executor ){                        
      QCommand* comm = new QCommand(NULL); 
      m_Executor->appendCommand(comm);     
      /*TODO FIX ME*/                      
      sleep(1);                            
      m_Executor->pauseExecution(false);   
  }                                        
}

