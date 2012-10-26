#ifndef QPLUGINLOADEREXT_H
#define QPLUGINLOADEREXT_H
#include <QPluginLoader>
#include <QObject>
#include <QMultiMap>
#include "qt/QpluginObjectsInterface.h"

class QPluginLoaderExt : public QPluginLoader
{
    Q_OBJECT
public:
    explicit QPluginLoaderExt(const QString &fileName,QObject *parent = 0);
    ~QPluginLoaderExt();
    QPluginObjectsInterface *instance();
    void closeSafety();
signals:
    void allObjectsDestroyed( QObject * );
public slots:
    void instanceDestroyed(QObject *);
protected:
    QPluginObjectsInterface* m_instance;

    static  QMultiMap<QString, QPluginLoaderExt*> m_Ploaders;
    static int ctr;
    int m_ctr;

signals:
    void close_all_objects();
};

#endif // QPLUGINLOADEREXT_H
