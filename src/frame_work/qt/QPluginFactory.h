#ifndef PLUGIN_DESCRIPTOR_H
#define PLUGIN_DESCRIPTOR_H
#include "base/global.h"
#include "base/global.h"
#include "QPluginLoaderExt.h"
#include "qt/PluginDescription.h"
#include"qt/QPluginObjectsInterface.h"
#include<QString>
#include<QIcon>
#include<QMutex>
#include<QMessageBox>

//#define ENABLE_VERBOSE_DUMP
#include "base/debug.h"

class FRAME_WORKSHARED_EXPORT QPluginFactory:public QObject{
    Q_OBJECT
public:
    explicit QPluginFactory( const char *name, QObject* parent = 0 );
    ~QPluginFactory();

    QObject* cretate_plugin_object( QObject *parent = 0 );

    const PluginDescription getDescription( ) const
    {
        return m_PluginDecription;
    }

    bool         is_enabled() const;

    void  enable( bool enbl);

public slots:
    void allObjectsDestoyed(QObject* obj);

protected:
    void    read_plugin_description();
    QPluginObjectsInterface *cast_to_plugin_interface( QObject* object );

protected:
    QMutex            m_Lock;
    QPluginLoaderExt* m_loader;
    PluginDescription m_PluginDecription;
    int               state;
};


void operator<<(  QDebug  Ostr, const QPluginFactory* in);

#endif // PLUGIN_DESCRIPTOR_H
