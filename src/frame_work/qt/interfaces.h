#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QList>
#include <QIcon>


typedef enum{
  FRAME_WORK,
  PORT_IO,
  DATA_OUT,
  UNDEFINED
}InterfaceType_t;



class plugin_interface{
public:
    virtual InterfaceType_t        type()                 = 0;
    virtual const char*            name() const           = 0;
    virtual const char*            category() const       = 0;
    virtual const char*            version() const        = 0;
    virtual const char*            description() const    = 0;
    virtual const QIcon            icon() const           = 0;
    virtual       QObject*         createObject( QObject *parent ) = 0;

};

#endif
