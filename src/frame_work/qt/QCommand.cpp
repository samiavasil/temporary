
#include "qt/QCommand.h"
#include "qt/QFrameWork.h"

QCommand::QCommand(QFrameWork * fWork) {
  
}

QCommand::~QCommand() {
  qDebug("QCommand Deleted");
}

/**
 * Command handler
 */
int QCommand::handler() const {
  static int a;                              
  int ret =  1;                              
  a++;                                       
  if(a >= 1000 ){                            
      ret =  0;                              
      DEBUG("QCommand Finished");            
  }                                          
  else{                                      
      if( a == 1 ){                          
          DEBUG("QCommand Execution start"); 
      }                                      
  }                                          
                                             
  return ret;                                
}

