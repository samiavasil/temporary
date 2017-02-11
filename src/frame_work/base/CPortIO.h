#ifndef _CPORTIO_H
#define _CPORTIO_H


#include "global.h"
class FRAME_WORKSHARED_EXPORT CPortIO {
public:
typedef enum{       
  SIMULATOR_IO ,    
  SERIALPORT_IO,    
  USBPORT_IO,
  UNDEFINED_IO
} portIo_type;      

  public:
    CPortIO();

    virtual ~CPortIO();

    virtual int64 bytesAvailable() = 0;

    virtual int64 read(char * data, const int64 maxlen) = 0;

    virtual int64 write(const char * data, const qint64 len) = 0;

    virtual int64 write(const char * data) = 0;

    virtual int open() = 0;

    virtual void close() = 0;

    virtual void readyReadSignal() = 0;


  protected:
    portIo_type m_PortType;


  public:
    CPortIO::portIo_type type();

};
#endif
