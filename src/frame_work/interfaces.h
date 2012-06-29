#ifndef INTERFACES_H
#define INTERFACES_H

#include <QtPlugin>
#include <QList>
#include "frame_work_global.h"
class QFrameWork;
class FRAME_WORKSHARED_EXPORT AnyTypeInterface{
public:
    virtual ~AnyTypeInterface() {}
    virtual QList<QObject*> getInterfaces()= 0;
    virtual const char* name() const = 0;
};

class FRAME_WORKSHARED_EXPORT FrameWorkInterface{
public:
    virtual ~FrameWorkInterface() {}
    virtual const char* name() = 0;
    virtual  QFrameWork* getFrameWork() = 0;
};

class FRAME_WORKSHARED_EXPORT IoInterface {
public:
    virtual ~IoInterface () {}
    virtual const char* name() const = 0;
};


Q_DECLARE_INTERFACE(AnyTypeInterface,
                    "vvv.moita.frame_work.AnyTypeInterface/1.0")
Q_DECLARE_INTERFACE(FrameWorkInterface,
                    "vvv.moita.frame_work.FrameWorkInterface/1.0")
Q_DECLARE_INTERFACE(IoInterface,
                    "vvv.moita.frame_work.IoInterface/1.0")

#endif // INTERFACES_H
