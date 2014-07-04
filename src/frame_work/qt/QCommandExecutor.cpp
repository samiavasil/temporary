
#include "qt/QCommandExecutor.h"
#include "base/CCommand.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QCommandExecutor::QCommandExecutor(QObject * parent) :QThread(parent),m_mutex(QMutex::Recursive){
  m_timer = NULL;
}

QCommandExecutor::~QCommandExecutor() {
  int ret = NO_ERR;                                              
  DEBUG << "Destroy Command Executor";

  if( 0 == isRunning() ){
       ret = stopExecution();
  }

  if( NO_ERR != ret ){
     DEBUG << " Can't terminate Command Executor thread corectly";
  }                                                              
  if( m_timer ){
      m_timer->deleteLater();
  }
}

/**
 * Append new command to queue.
 */
int QCommandExecutor::appendCommand_internal(CCommand * command) {
  int ret = NO_ERR;                                     
  if( command ){                                        
      QCommand* qcomm = (QCommand *)command;            
      /*TODO - Should add command type validation code*/
      if( qcomm ){                                      
        m_commands.append( qcomm );                     
      }                                                 
  }                                                     
  else{                                                 
      ret = WRONG_PARAMS;                               
  }                                                     
  return ret; 
}

/**
 * Implementation of virtual removeCommand function... Use this function only when object is locked. 
 * It is will be good if you don't use it ( only implement it  ), because it is used in base class where 
 * have a object lock ( for more see CCOmandExecutor souce ).
 */
int QCommandExecutor::removeCommand(int comm) {
  int ret = WRONG_PARAMS;                   
  QCommand * cmd = m_commands.takeAt(comm); 
  if( cmd ){                                
      cmd->deleteLater();                   
      ret = NO_ERR;                         
  }                                         
  return ret;                               
}

/**
 * Flush all commands from Queue
 */
void QCommandExecutor::flushCommands_internal() {
  QCommand * comm;                 
  while( 0 < m_commands.count() ){ 
      comm = m_commands.takeAt(0); 
      if( comm ){                  
          comm->deleteLater();     
      }                            
  }                                                          
}

/**
 * Pause execution of loaded in queue commands 
 */
int QCommandExecutor::pauseExecution() {
  int ret = NO_ERR;                                  
  lockObject();                                      
  if( true == isRunning() ){                         
      if( m_timer ){                                 
              emit stopTimer();
      }                                              
      else{                                          
          ret = NULL_POINTER;                        
      }                                              
  }                                                  
  else{                                              
      /*Thread isn't running*/                       
      ret = SOME_ERROR;                              
  }                                                  
  unlockObject();                                    
  return ret;             
}

/**
 * Contiinue execution of loaded in queue commands after pause
 */
int QCommandExecutor::continueExecution(){
    int ret = NO_ERR;
    lockObject();
    if( true == isRunning() ){
        if( m_timer ){
                DEBUG << "Run Command Execution loop";
                emit runTimer(m_CommandLoopTime);
        }
        else{
            ret = NULL_POINTER;
        }
    }
    else{
        /*Thread isn't running*/
        ret = SOME_ERROR;
    }
    unlockObject();
    return ret;
}

/**
 * Start commands execution - run thread  and timer. Comands are exectuted repeatedly with timer.
 */
int QCommandExecutor::startExecution() {

  if( 0 == isRunning() ){
       start();
  }
  return NO_ERR;
}

/**
 * Finish commands execution and free all - normall finish.
 */
int QCommandExecutor::stopExecution() {
  
      int rt = NO_ERR;
      pauseExecution();
      exit(0);
      DEBUG << "FINISH!!!! QCommandExecutor";
      if( false == wait( 10000 ) ){
         DEBUG << "FINISH!!!! Not Finished QCommandExecutor!! Try to terminate??";
         terminate();//TODO ????? this no goood ???
         rt = SOME_ERROR;
      }
      else
      {
          DEBUG << "FINISH!!!! FINISHED QCommandExecutor";
      }
      return rt;
}

int QCommandExecutor::executeCommand(int comm_num) {
  int ret = 0;                                           
  CCommand * comm = m_commands.value( comm_num, NULL);   
  if( comm ){                                            
      ret = comm->handler();                             
  }                                                      
  return ret;                                            
}

void QCommandExecutor::lockObject() {
  m_mutex.lock();
}

void QCommandExecutor::unlockObject() {
  m_mutex.unlock();
}

void QCommandExecutor::startTimer() {
  if( 0 == m_timer ){                         
       DEBUG << "Timer isn't initialised";
  } 
  emit runTimer(m_CommandLoopTime);                                        
}

void QCommandExecutor::run() {
    int retCode = NO_ERR;
    DEBUG << "Run Command Executor thread";
   // lockObject();
    retCode = initTimer();
  //  unlockObject();
    emit initReady();
    retCode = exec();                                           
    DEBUG << "Exit Command Executor Thread with code: " << retCode;
}

int QCommandExecutor::initTimer() {
  if( NULL == m_timer ){                                                                                       
      m_timer = new QTimer();                                                                                  
      m_timer->setSingleShot( true );                                                                          
      connect( this, SIGNAL(runTimer(int)),m_timer , SLOT( start(int) ),Qt::AutoConnection );                  
      connect( m_timer, SIGNAL(timeout()), this, SLOT( timerHandlerExecuteCommands() ),Qt::DirectConnection ); 
  }                                                                                                            
  return NO_ERR;                                                                                               
}

/**
 * Timer based Commands handling loop
 */
void QCommandExecutor::timerHandlerExecuteCommands() {
  timerHandlerExecuteAllCommands();
}

