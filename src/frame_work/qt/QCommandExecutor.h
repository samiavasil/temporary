#ifndef _QCOMMANDEXECUTOR_H
#define _QCOMMANDEXECUTOR_H

#include "base/global.h"
#include <QThread>
#include <QMutex>
#include <QList>

class QCommand;
class QTimer;

class FRAME_WORKSHARED_EXPORT QCommandExecutor : public QThread {
    Q_OBJECT

public:
    QCommandExecutor(QObject * pParent = 0);

    virtual ~QCommandExecutor();
    /**
     * Append new command to queue.
     */
    virtual int appendCommand(QCommand *pComm);

    virtual void run();

    /**
     * Flush all commands from Queue
     */
    virtual void flushCommands();

    virtual int getCommNum();

    virtual void setCommandLoopTime(int timeMs);

    virtual int getCommandLoopTime();

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

    virtual int executeCommand(int commNum);
    /**
     * Implementation of virtual removeCommand function... Use this function only when object is locked.
     * It is will be good if you don't use it ( only implement it  ), because it is used in base class where
     * have a object lock ( for more see CCOmandExecutor souce ).
     */
    virtual int removeCommand(int comm);

    virtual void startTimer();

protected:
    int initTimer();

protected slots:
    /**
     * Timer based Commands handling loop
     */
    void timerHandlerExecuteCommands();

signals:
    void runTimer(int time);

    void stopTimer();

    void initReady();

protected:

    QList<QCommand*> m_commands;

    QMutex m_mutex;

    QTimer* m_timer;
    /**
     * Command loop execution time. All available loops are servised on every m_CommandLoopTime mili seconds.
     */
    int m_CommandLoopTime;

};


#endif
