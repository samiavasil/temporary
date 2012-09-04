#ifndef _QPORTIOSIMULATOR_H
#define _QPORTIOSIMULATOR_H


#include <QObject>

#include "base/CPortIO.h"

class QPortIOSimulator : public QObject, public CPortIO {
Q_OBJECT

  public:
    QPortIOSimulator();

    virtual int64 bytesAvailable();

    virtual int64 read(char * data, const int64 maxlen);

    virtual int64 write(const char * data, const qint64 len);

    virtual int open();

    virtual int close();

    virtual void readyReadSignal();

};
#endif
