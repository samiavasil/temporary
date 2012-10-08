#ifndef QPLUGINLOADEREXT_H
#define QPLUGINLOADEREXT_H
#include <QPluginLoader>
#include <QObject>
#include <QList>

class QPluginLoaderExt : public QPluginLoader
{
    Q_OBJECT
public:
    explicit QPluginLoaderExt(const QString &fileName,QObject *parent = 0);
    ~QPluginLoaderExt();
    QObject *instance();
signals:
    
public slots:
    void instanceDestroyed(QObject *);
protected:
      QObject* m_instance;
static  QList<QPluginLoaderExt*> m_Ploaders;
static int ctr;
int m_ctr;
};

#endif // QPLUGINLOADEREXT_H
