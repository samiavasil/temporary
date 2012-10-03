#ifndef QPLUGINLOADEREXT_H
#define QPLUGINLOADEREXT_H
#include <QPluginLoader>
#include <QObject>

class QPluginLoaderExt : public QPluginLoader
{
    Q_OBJECT
public:
    explicit QPluginLoaderExt(const QString &fileName,QObject *parent = 0);
    ~QPluginLoaderExt(){
       qDebug("Destroy QPluginLoaderExt");
    }

    QObject *instance();
signals:
    
public slots:
    void instanceDestroyed(QObject *);
protected:
      QObject* m_instance;
};

#endif // QPLUGINLOADEREXT_H
