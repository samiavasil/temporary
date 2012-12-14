#ifndef _QSERIALPORTIO_H
#define _QSERIALPORTIO_H


#include <QObject>

#include "base/CPortIO.h"
#include<qextserialport.h>

namespace Ui {
  class SerialPortConfig;
}


class QSerialPortIO : public QextSerialPort, public CPortIO {
Q_OBJECT

  public:
    QSerialPortIO( QextSerialPort::QueryMode = QextSerialPort::Polling );

    ~QSerialPortIO();
    inline int64 bytesAvailable() {
      return QextSerialPort::bytesAvailable();
    }

    inline int64 read(char * data, const int64 maxlen) {
      return QextSerialPort::read( data, maxlen );
    }

    inline int64 write(const char * data, const qint64 len) {
      return QextSerialPort::write( data, len );
    }

    inline int64 write( const char * data ) {
      return QextSerialPort::write( data );
    }

    inline int open() {
      return QextSerialPort::open( QIODevice::ReadWrite );
    }

    inline void close() {
       QextSerialPort::close();
    }/**/
    void showPortConfiguration( QWidget* parent );

protected:
    void initUi();
signals:
    void readyReadSignal();
protected slots:
    void dataReady();
    void setPortName( const QString portName );
    void setQueryMode( int act );
    void setBaudRate( int rate );
    void setParity( int par );
    void setStopBits(int );
    void setFlowControl(int);
    void setTimeout(int);
protected:
    QextSerialPort m_Serial; !!! Triabwa da stane taka!!! Parwo updeitni bouml-a
private:
    Ui::SerialPortConfig *ui;
};
#endif
