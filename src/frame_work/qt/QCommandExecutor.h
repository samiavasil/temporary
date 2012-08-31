#ifndef _QCOMMANDEXECUTOR_H
#define _QCOMMANDEXECUTOR_H


#include <QThread>

#include "base/CCommandExecutor.h"
#include <QTimer>

#include "qt/QCommand.h"
#include <QMutex>

#include <QList>

#include <QObject>


class CCommand;

class QCommandExecutor : protected QThread, public CCommandExecutor {
Q_OBJECT

  public:
    QCommandExecutor(QObject * parent = 0);

    ~QCommandExecutor();

    /**
     * Append new command to queue.
     */
    virtual int appendCommand(CCommand * command);

    /**
     * Implementation of virtual removeCommand function... Use this function only when object is locked. 
     * It is will be good if you don't use it ( only implement it  ), because it is used in base class where 
     * have a object lock ( for more see CCOmandExecutor souce ).
     */
    virtual int removeCommand(int comm);


  protected:
    virtual int executeCommand(int comm_num);

    virtual void lockObject();

    virtual void unlockObject();


  public:
    /**
     * Flush all commands from Queue
     */
    virtual void flushCommands();

    inline virtual int getCommNum();

    /**
     * Pause execution of loaded in queue commands 
     */
    virtual int pauseExecution(bool pause);

    /**
     * Start commands execution - run thread  and timer. Comands are exectuted repeatedly with timer.
     */
    virtual int startExecution(bool starting);


  protected:
    virtual void startTimer();


  public:
    void run();


  protected:
    int initTimer();

    QList<QCommand*> m_commands;

    QMutex m_mutex;

    QTimer* m_timer;

protected slots:
    /**
     * Timer based Commands handling loop
     */
    void timerHandlerExecuteCommands();

signals:
    void runTimer(int time);

    void stopTimer();

};
inline int QCommandExecutor::getCommNum() {
  return m_commands.count();
}

#endif
