#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include "frame_work_global.h"
#include <QDialog>
#include <QString>
#include <QMap>
#include "QPluginLoaderExt.h"
#include <QTableWidgetItem>
#include "qt/QPluginFabrique.h"
#include "qt/QpluginFilter.h"

#include "interfaces.h"
namespace Ui {
class PluginList;
}



class FRAME_WORKSHARED_EXPORT QPluginList : public QDialog /* singleton */
{
    Q_OBJECT
    
protected:
    explicit QPluginList(QWidget *parent = 0);
public:
    ~QPluginList();
    static QPluginList* Instance();

    QList<PluginDescription> getAllPlugins( const QpluginFilter &filter );
    QObject* cretate_plugin_object( PluginDescription &desc , QObject *parent = 0 );
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

protected:
    void readPluginsDir( );
    void populatePluginList();


signals:
    void pluginsUpdate();
public slots:
    void reloadPlugins( );
protected slots:
    void listSelectionChanged(QTableWidgetItem *item);


protected:
    static QPluginList* m_This;
    static QMap< QString, QPluginFabrique*  > m_PluginList;
private:
    Ui::PluginList *ui;


};

#endif // PLUGINLIST_H
