#ifndef _QPLUGINLOADEREXT_H
#define _QPLUGINLOADEREXT_H


#include <QPluginLoader>

#include <QMultiMap>


class QPluginObjectsInterface;

class QPluginLoaderExt : public QPluginLoader {
Q_OBJECT

  protected:
    static QMultiMap<QString, QPluginLoaderExt*> m_Ploaders;

    /**
     * DELL ME
     */
    static int ctr;


  public:
    explicit QPluginLoaderExt(const QString & fileName, QObject * parent = 0);

    virtual ~QPluginLoaderExt();

    void closeSafety();

    QPluginObjectsInterface* instance();

signals:
    void allObjectsDestroyed(QObject * );

    void close_all_objects();


  protected:
    QPluginObjectsInterface* m_instance;

    int m_ctr;

public slots:

  public:
    void instanceDestroyed(QObject * obj);

};
#endif
