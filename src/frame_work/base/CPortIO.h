#ifndef _CPORTIO_H
#define _CPORTIO_H


class CPortIO {
  public:
    virtual int64 read(char * data, const int64 maxlen) = 0;

    virtual int64 write(const char * data, const qint64 len) = 0;

    virtual int open() = 0;

    int close();

    void readyReadSignal();

};
#endif
