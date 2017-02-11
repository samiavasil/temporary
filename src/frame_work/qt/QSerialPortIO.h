#ifndef _QSERIALPORTIO_H
#define _QSERIALPORTIO_H


#include "base/global.h"
#include "qt/QPortIO.h"
#include <qtserial/qextserialport.h>



namespace Ui {
  class SerialPortConfig;
}

class FRAME_WORKSHARED_EXPORT QSerialPortIO : public QPortIO {
Q_OBJECT

  public:
    QSerialPortIO(QObject * parent = 0, const QextSerialPort::QueryMode & mode = QextSerialPort::Polling);

    virtual ~QSerialPortIO();

    void showPortConfiguration(QWidget * parent);

    inline int64 bytesAvailable();

    inline int64 read(char * data, const int64 maxlen);

    inline int64 write(const char * data, const qint64 len);

    inline int64 write(const char * data);

    inline int open();

    inline void close();

signals:
    void readyReadSignal();


  protected:
    void initUi();

protected slots:
    void dataReady();

    void setPortName(const QString & portName);

    void setQueryMode(int act);

    void setBaudRate(int rate);

    void setParity(int par);

    void setStopBits(int stop);

    void setFlowControl(int flow);

    void setTimeout(int timeout_Ms);


  private:
    Ui::SerialPortConfig * ui;


  protected:
    QextSerialPort m_Serial;

};
inline int64 QSerialPortIO::bytesAvailable() {
  return m_Serial.bytesAvailable();
}

inline int64 QSerialPortIO::read(char * data, const int64 maxlen) {
  return m_Serial.read( data, maxlen );
}

inline int64 QSerialPortIO::write(const char * data, const qint64 len) {
  return m_Serial.write( data, len );
}

inline int64 QSerialPortIO::write(const char * data) {
  return m_Serial.write( data );
}

inline int QSerialPortIO::open() {
  return m_Serial.open( QIODevice::ReadWrite );
}

inline void QSerialPortIO::close() {
  m_Serial.close();
}

#endif
