#ifndef _QPORTIO_H
#define _QPORTIO_H

#include "base/global.h"
#include <QWidget>
#include<QPointer>


class FRAME_WORKSHARED_EXPORT QPortIO : public QObject {
    Q_OBJECT
public:
    typedef enum{
        SIMULATOR_IO ,
        SERIALPORT_IO,
        USBPORT_IO,
        UNDEFINED_IO
    } portIo_type;

public:
    explicit QPortIO(QObject * parent);

    virtual ~QPortIO();

    virtual int64 bytesAvailable() = 0;

    virtual int64 read(char * data, const int64 maxlen) = 0;

    virtual int64 write(const char * data, const qint64 len) = 0;

    virtual int64 write(const char * data) = 0;

    virtual int open() = 0;

    virtual void close() = 0;

    virtual void readyReadSignal() = 0;

    virtual void showPortConfiguration(QWidget * parent) = 0;

    QPortIO::portIo_type type();

protected:
  portIo_type m_PortType;

signals:
    void readyReadBytesSignal();

protected:
    QPointer<QWidget> m_PioWidget;
};
#endif
