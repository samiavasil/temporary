#ifndef _QPORTIOSIMULATOR_H
#define _QPORTIOSIMULATOR_H


#include "frame_work_global.h"
#include <QByteArray>

#include <QMutex>

#include "qt/QPortIO.h"

class FRAME_WORKSHARED_EXPORT QPortIOSimulator : public QPortIO {
Q_OBJECT

  public:
    QPortIOSimulator(QObject * parent = 0);

    virtual ~QPortIOSimulator();

    virtual int64 bytesAvailable();

    virtual int64 read(char * data, const int64 maxlen);

    virtual int64 write(const char * data, const qint64 len);

    virtual int64 write(const char * data);

    virtual int open();

    virtual void close();

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
