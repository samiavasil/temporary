#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QDialog>
#include <QString>
#include <QMap>
#include "QPluginLoaderExt.h"
#include <QTableWidgetItem>
#include "plugin_descriptor.h"
#include "interfaces.h"
namespace Ui {
class PluginList;
}



class QPluginList : public QDialog
{
    Q_OBJECT
    
public:
    explicit QPluginList(QWidget *parent = 0);
    ~QPluginList();
    QList<QPluginLoaderExt*> getAllActivePlugins( InterfaceType_t type );
    
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

protected:
    void readPluginsDir( );
    void populatePluginList();


signals:
    void reload();
public slots:
    void reloadPlugins( );
protected slots:
    void listSelectionChanged(QTableWidgetItem *item);


protected:
    QMap< QString, plugin_descriptor*  > m_PluginList;
private:
    Ui::PluginList *ui;


};

#endif // PLUGINLIST_H
