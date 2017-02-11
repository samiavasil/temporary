#ifndef _QCOMMANDEXECUTOR_H
#define _QCOMMANDEXECUTOR_H


#include "base/global.h"
#include <QThread>

#include "base/CCommandExecutor.h"
#include <QTimer>

#include "qt/QCommand.h"
#include <QMutex>

#include <QList>

#include <QObject>


class CCommand;

class FRAME_WORKSHARED_EXPORT QCommandExecutor : public QThread, public CCommandExecutor {
Q_OBJECT

  public:
    QCommandExecutor(QObject * parent = 0);

    virtual ~QCommandExecutor();

public slots:

    /**
     * Pause execution of loaded in queue commands
     */
    virtual int pauseExecution();
    /**
     * Contiinue execution of loaded in queue commands after pause
     */
    virtual int continueExecution();

    /**
     * Run thread  and timer. Comands are exectuted repeatedly with timer.
     */
    virtual int startExecution();
    /**
     * Finish commands execution and free all - normall finish.
     */
    virtual int stopExecution();

  protected:
    virtual int executeCommand(int comm_num);
    /**
     * Implementation of virtual removeCommand function... Use this function only when object is locked.
     * It is will be good if you don't use it ( only implement it  ), because it is used in base class where
     * have a object lock ( for more see CCOmandExecutor souce ).
     */
    virtual int removeCommand(int comm);

    /**
     * Append new command to queue.
     */
    virtual int appendCommand_internal(CCommand * command);
     /**
     * Flush all commands from Queue
     */
    virtual void flushCommands_internal();

    inline virtual int getCommNum_internal();


    virtual void lockObject();

    virtual void unlockObject();

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

    void initReady();
};

inline int QCommandExecutor::getCommNum_internal() {
  return m_commands.count();
}

#endif
