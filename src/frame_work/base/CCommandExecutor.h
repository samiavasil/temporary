#ifndef _CCOMMANDEXECUTOR_H
#define _CCOMMANDEXECUTOR_H

#include "global.h"
class CCommand;

class CCommandExecutor {
  public:
    CCommandExecutor();

    /**
     * Append new command to queue.
     */
    virtual int appendCommand(CCommand * command) = 0;

    virtual int removeCommand(int comm) = 0;

    /**
     * Flush all commands from Queue
     */
    virtual void flushCommands() = 0;

    /**
     * Pause execution of loaded in queue commands 
     */
    virtual int pauseExecution(bool pause) = 0;

    /**
     * Start commands execution - run thread  and timer. Comands are exectuted repeatedly with timer.
     */
    virtual int startExecution(bool starting) = 0;


  protected:
    virtual void startTimer() = 0;

    /**
     * Timer based Commands handling loop
     */
    inline virtual void timerHandlerExecuteAllCommands();

    virtual int executeCommand(int comm_num) = 0;


  public:
    virtual int getCommNum() = 0;

    /**
     * Set command loop time
     */
    virtual void setCommandLoopTime(int time_ms);

    /**
     * Return command loop time [ms]
     */
    virtual int getCommandLoopTime();


  protected:
    virtual void lockObject() = 0;

    virtual void unlockObject() = 0;

    /**
     * Command loop execution time. All available loops are servised on every m_CommandLoopTime mili seconds.
     */
    int m_CommandLoopTime;

};
/**
 * Timer based Commands handling loop
 */
inline void CCommandExecutor::timerHandlerExecuteAllCommands() {
  lockObject();                        
  int com_num = getCommNum();          
  for( int i = 0; i < com_num; i++ ){  
      if( 0 == executeCommand( i ) )   
      {                                
          removeCommand(i);            
      }                                
  }                                    
  if( 0 < getCommNum() ){              
    startTimer( );   
  }                                    
  unlockObject();                      
}

#endif
