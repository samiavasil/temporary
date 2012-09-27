#ifndef PLUGINLIST_H
#define PLUGINLIST_H

#include <QDialog>
#include <QString>
#include <QMap>
#include <QPluginLoader>

namespace Ui {
class PluginList;
}

class QPluginList : public QDialog
{
    Q_OBJECT
    
public:
    explicit QPluginList(QWidget *parent = 0);
    ~QPluginList();
    
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

protected:
    void readPluginsDir( );
    void populatePluginList();

protected slots:
    void listSelectionChanged();

protected:
    QMap< QString,QPluginLoader*  > m_PluginList;
private:
    Ui::PluginList *ui;


};

#endif // PLUGINLIST_H
