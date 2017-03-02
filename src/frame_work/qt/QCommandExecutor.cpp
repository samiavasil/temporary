#include <QObject>
#include <QTimer>
#include "qt/QCommand.h"
#include "qt/QCommandExecutor.h"

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

QCommandExecutor::QCommandExecutor(QObject * pParent) :QThread(pParent),m_mutex(QMutex::Recursive){
  m_CommandLoopTime = 10;
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

int QCommandExecutor::appendCommand(QCommand *pComm)
{
    int ret = NO_ERR;
    m_mutex.lock();
    if( pComm ){
          m_commands.append( pComm );
    }
    else{
        ret = WRONG_PARAMS;
    }
    m_mutex.unlock();
    return ret;
}

void QCommandExecutor::flushCommands(){
    m_mutex.lock();
    QCommand * comm;
    while( 0 < m_commands.count() ){
        comm = m_commands.takeAt(0);
        if( comm ){
            comm->deleteLater();
        }
    }
    m_mutex.unlock();
}

int QCommandExecutor::getCommNum() {
    int count;
    m_mutex.lock();
    count = m_commands.count();
    m_mutex.unlock();
    return count;
}

/**
 * Set command loop time
 */
void QCommandExecutor::setCommandLoopTime(int timeMs) {
    m_CommandLoopTime = timeMs;
}

/**
 * Return command loop time [ms]
 */
int QCommandExecutor::getCommandLoopTime() {
  return m_CommandLoopTime;
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
 * Pause execution of loaded in queue commands 
 */
int QCommandExecutor::pauseExecution() {
  int ret = NO_ERR;                                  
  m_mutex.lock();
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
  m_mutex.unlock();
  return ret;             
}

/**
 * Contiinue execution of loaded in queue commands after pause
 */
int QCommandExecutor::continueExecution(){
    int ret = NO_ERR;
    m_mutex.lock();
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
    m_mutex.unlock();
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

int QCommandExecutor::executeCommand(int commNum) {
  int ret = 0;                                           
  QCommand * comm = m_commands.value( commNum, NULL);
  if( comm ){                                            
      ret = comm->handler();                             
  }                                                      
  return ret;                                            
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
   // m_mutex.lock();
    retCode = initTimer();
  //  m_mutex.unlock();
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
  m_mutex.lock();
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
  m_mutex.unlock();
}

