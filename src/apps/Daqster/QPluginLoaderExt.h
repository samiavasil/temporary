#ifndef QPLUGINLOADEREXT_H
#define QPLUGINLOADEREXT_H
#include <QPluginLoader>
#include <QObject>

class QPluginLoaderExt : public QPluginLoader
{
    Q_OBJECT
public:
    explicit QPluginLoaderExt(QObject *parent = 0);
    
    QObject *instance();
signals:
    
public slots:
    void instanceDestroyed(QObject *);
protected:
      QObject* m_instance;
};

#endif // QPLUGINLOADEREXT_H
