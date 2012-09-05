
#include "qt/QCommand.h"
#include "qt/QFrameWork.h"
#include "base/CPortIO.h"
QCommand::QCommand(QFrameWork * fWork) {
  m_fWork = fWork;
  a=0;         
}

QCommand::~QCommand() {
  qDebug("QCommand Deleted");
}

/**
 * Command handler
 */
int QCommand::handler() {
  int ret =  1;                                            
  a++;                                                     
  if(a >= 100 ){
      ret =  0;                                            
      DEBUG("QCommand Finished");                          
  }                                                        
  else{                                                    
      if( a == 1 ){                                        
          DEBUG("QCommand Execution start");               
      }                                                    
      if( m_fWork ){                                          
         CPortIO* port = m_fWork->getPortIO();                
         if( port ){                                       
             int randNum = qrand()%120;                    
             u8 data[randNum];                             
             for( int i=0; i< randNum; i++ ){              
                 data[i] = qrand();                        
             }                                             
             port->write((const char *) data,randNum);     
         }                                                 
      }                                                    
                                                           
  }                                                        
                                                           
  return ret;                                              
}

