#ifndef _QSERIALPORTIO_H
#define _QSERIALPORTIO_H


#include <QObject>

#include "base/CPortIO.h"
#include<qextserialport.h>
#include"qt/QPortIO.h"

namespace Ui {
  class SerialPortConfig;
}

class QextSerialPort;

class QSerialPortIO : public QPortIO, public CPortIO {
Q_OBJECT

  public:
    QSerialPortIO( QextSerialPort::QueryMode = QextSerialPort::Polling );

    ~QSerialPortIO();
    inline int64 bytesAvailable() {
      return m_Serial.bytesAvailable();
    }

    inline int64 read(char * data, const int64 maxlen) {
      return m_Serial.read( data, maxlen );
    }

    inline int64 write(const char * data, const qint64 len) {
      return m_Serial.write( data, len );
    }

    inline int64 write( const char * data ) {
      return m_Serial.write( data );
    }

    inline int open() {
      return m_Serial.open( QIODevice::ReadWrite );
    }

    inline void close() {
       m_Serial.close();
    }/**/
    void showPortConfiguration( QWidget* parent );
signals:
    void readyReadSignal();
protected:
    void initUi();

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
    QextSerialPort m_Serial;
private:
    Ui::SerialPortConfig *ui;
};
#endif
