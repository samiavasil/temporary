#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QList>
#include <QIcon>
#include "frame_work_global.h"

class QFrameWork;
typedef enum{
  FRAME_WORK,
  PORT_IO
}InterfaceType_t;

class plugin_interface{
public:
    virtual     InterfaceType_t  type()           = 0;
    virtual const char*            name() const        = 0;
    virtual const char*            category() const    = 0;
    virtual const char*            version() const     = 0;
    virtual const char*            description() const = 0;
    virtual const QIcon            icon() const   = 0;
};

class FRAME_WORKSHARED_EXPORT AnyTypeInterface:public plugin_interface{
public:
    virtual ~AnyTypeInterface() {}
    virtual QList<QObject*> getInterfaces()= 0;

};

class FRAME_WORKSHARED_EXPORT FrameWorkInterface:public plugin_interface{
public:
    virtual ~FrameWorkInterface() {}
    virtual  QFrameWork* getFrameWork(QWidget* parent) = 0;
};

class FRAME_WORKSHARED_EXPORT IoInterface:public plugin_interface{
public:
    virtual ~IoInterface () {}
};


Q_DECLARE_INTERFACE(AnyTypeInterface,
                    "vvv.moita.frame_work.AnyTypeInterface/1.0")
Q_DECLARE_INTERFACE(FrameWorkInterface,
                    "vvv.moita.frame_work.FrameWorkInterface/1.0")
Q_DECLARE_INTERFACE(IoInterface,
                    "vvv.moita.frame_work.IoInterface/1.0")

#endif // INTERFACES_H
