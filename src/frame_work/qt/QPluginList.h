#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include "base/global.h"
#include <QString>
#include <QMap>
#include "QPluginLoaderExt.h"
#include <QTableWidgetItem>
#include "qt/QPluginFactory.h"
#include "qt/QPluginFilter.h"

#include "interfaces.h"
namespace Ui {
class PluginList;
}



class FRAME_WORKSHARED_EXPORT QPluginList:public QObject  /* singleton */
{
    Q_OBJECT
    
protected:
    explicit QPluginList( QObject* parent = 0 );
public:
    ~QPluginList();
    static QPluginList* Instance();
    static QList<PluginDescription> configurePlugins( const QPluginFilter &filter = QPluginFilter() );

    QList<PluginDescription> getAllPlugins( const QPluginFilter &filter );
    QObject* cretate_plugin_object( const PluginDescription &desc , QObject *parent = 0 );
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

protected:
    void readPluginsDir( );
    bool is_plugin_disabled( const QString &name );
    void readDisabledPlugins( );
signals:
    void pluginsUpdate();
    void setDescription( const QString &text );
public slots:

    void pluginEnable( PluginDescription desc, bool enble );
    void reloadPlugins( );
protected slots:
    void listSelectionChanged(const PluginDescription &desc);


protected:
    static QPluginList* m_This;
    static QMap< QString, QPluginFactory*  > m_PluginList;
private:

};

#endif // PLUGINLIST_H
