#ifndef QREGFACTORY_H
#define QREGFACTORY_H

#include <QMap>
#include <QSet>
#include <QString>
#include <QDebug>

#include "frame_work_global.h"

// Abstract factory from template, register classes at runtime.

template <typename T>
class FRAME_WORKSHARED_EXPORT QRegFactory
{
public:
    typedef T* (*CreateFunc)();

    static void Registrate(const QString& name, QRegFactory::CreateFunc func)
    {
        if ( GetRegistry().end() == GetRegistry().find(name) )
        {
            GetRegistry()[name] = func;
        }
    }

    static T* CreateInstance(const QString& name)
    {
        typename QMap<QString, QRegFactory::CreateFunc>::iterator it = GetRegistry().find(name);
        return it == GetRegistry().end() ? NULL : (it->second)();
    }

    static void GetRegList(QSet<QString>& outlist)
    {
        outlist.clear();
        //typename QMap<QString, QRegFactory::CreateFunc>::iterator it;
        typename QMap<QString, QRegFactory::CreateFunc>::iterator it;
        for ( it = GetRegistry().begin(); it != GetRegistry().end(); it++ )
        {
            outlist.insert(it.key());
        }
    }

    template <typename D>
    struct Registrator
    {
        Registrator(const QString& name)
        {
            QRegFactory::Registrate(name, D::CreateItem);
        }
    private: // non-copyable
        Registrator(const Registrator&);
        void operator=(const Registrator&);
    };

protected:
    static QMap<QString, QRegFactory::CreateFunc>& GetRegistry()
    {
        static QMap<QString, QRegFactory::CreateFunc> s_registry;
        qDebug() << "s_registry_ptr: "<<&s_registry;
        return s_registry;
    }
};

#include<QDebug>
class FRAME_WORKSHARED_EXPORT A{
public:
    A(){
     count++;
     im = count;
    }
    static A*  CreateItem(){
      return new A;
    }
    void printHoIm(){
        qDebug() << im;
    }
protected:
   static int count;
   int im;
};
int A::count;

 typedef QRegFactory<A> fact1_t;

#endif // QREGFACTORY_H
