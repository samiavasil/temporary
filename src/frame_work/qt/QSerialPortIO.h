#ifndef _QSERIALPORTIO_H
#define _QSERIALPORTIO_H


#include <QObject>

#include "base/CPortIO.h"

class QSerialPortIO : public QObject, public CPortIO {
Q_OBJECT

  public:
    QSerialPortIO();

    ~QSerialPortIO();

    virtual int64 bytesAvailable();

    virtual int64 read(char * data, const int64 maxlen);

    virtual int64 write(const char * data, const qint64 len);

    virtual int open();

    int close();

    void readyReadSignal();

};
#endif
