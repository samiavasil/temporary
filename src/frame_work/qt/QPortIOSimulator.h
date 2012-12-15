#ifndef _QPORTIOSIMULATOR_H
#define _QPORTIOSIMULATOR_H


#include <QObject>

#include "base/CPortIO.h"
#include <QByteArray>

#include <QMutex>
#include"qt/QPortIO.h"


class QPortIOSimulator : public QPortIO, public CPortIO {
Q_OBJECT

  public:
    virtual ~QPortIOSimulator();

    QPortIOSimulator(QObject *parent = 0);

    virtual int64 bytesAvailable();

    virtual int64 read(char * data, const int64 maxlen);

    virtual int64 write(const char * data, const qint64 len);
    virtual int64 write( const char * data );
    virtual int open();

    virtual void close();

    //virtual void readyReadSignal();
signals:
  void readyReadSignal();
  protected:
    void reloadSimulatorTask();

    QByteArray m_WriteData;

    QByteArray m_Data;

    QMutex m_Mutex;

    int m_ReadCounter;

    int m_WriteCounter;

    bool m_TaskRuned;

protected slots:
    void simulatorTask();

};
#endif
