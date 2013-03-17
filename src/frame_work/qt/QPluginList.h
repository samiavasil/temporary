#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QDialog>
#include <QString>
#include <QMap>
#include "QPluginLoaderExt.h"
#include <QTableWidgetItem>
#include "qt/QPluginDescriptor.h"
#include "interfaces.h"
namespace Ui {
class PluginList;
}



class QPluginList : public QDialog /* singleton */
{
    Q_OBJECT
    
protected:
    explicit QPluginList(QWidget *parent = 0);
public:
    ~QPluginList();
    static QPluginList* Instance();

    QList<QPluginDescriptor*> getAllActivePlugins( InterfaceType_t type );
    
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
    static QPluginList* m_This;
    static QMap< QString, QPluginDescriptor*  > m_PluginList;
private:
    Ui::PluginList *ui;


};

#endif // PLUGINLIST_H
