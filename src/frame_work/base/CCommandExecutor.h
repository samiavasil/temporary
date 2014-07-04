#ifndef _CCOMMANDEXECUTOR_H
#define _CCOMMANDEXECUTOR_H

#include "global.h"
class CCommand;

class CCommandExecutor {
  public:
    CCommandExecutor();

    virtual ~CCommandExecutor();

    /**
     * Append new command to queue.
     */
    virtual int appendCommand(CCommand * command) {
       int ret;
       lockObject();
       ret = appendCommand_internal(command);
       unlockObject();
       return ret;
    }

    /**
     * Flush all commands from Queue
     */
    virtual void flushCommands(){
        lockObject();
        flushCommands_internal();
        unlockObject();
    }

    virtual int getCommNum() {
        int count;
        lockObject();
        count = getCommNum_internal();
        unlockObject();
        return count;
    }

    /**
     * Pause execution of loaded in queue commands 
     */
    virtual int pauseExecution() = 0;
    /**
     * Contiinue execution of loaded in queue commands after pause
     */
    virtual int continueExecution() = 0;

    /**
     * Start commands execution
     */
    virtual int startExecution() = 0;

    /**
     * Stop commands execution
     */
    virtual int stopExecution() = 0;

  protected:
    virtual void startTimer() = 0;

    /**
     * Timer based Commands handling loop
     */
    inline virtual void timerHandlerExecuteAllCommands();

    virtual int executeCommand(int comm_num) = 0;
    virtual int  removeCommand(int comm)     = 0;
    /**
     * Append new command to queue.
     */
    virtual int  appendCommand_internal(CCommand * command) = 0;
    virtual void flushCommands_internal()                   = 0;
    virtual int  getCommNum_internal()                      = 0;

  public:


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
     for( int i = 0; i < getCommNum(); i++ ){
        if( 0 == executeCommand( i ) )   
        {                                
            removeCommand(i);
            i--;
        }                                
    }                                    
    if( 0 < getCommNum() ){              
      startTimer( );   
    }                                    
    unlockObject();                               
}

#endif
