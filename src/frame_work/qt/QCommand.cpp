
#include "qt/QCommand.h"

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
     if(a < 1000 ){                       
         qDebug("QCommand Executed %d",a);
     }                                    
     else{                                
         ret =  0;                        
         qDebug("QCommand Finished");     
     }                                    
                                          
   return ret;                            
}

