#ifndef QPLUGINLISTWIDGED_H
#define QPLUGINLISTWIDGED_H

#include <QWidget>
#include <QListWidget>
#include "qt/QPluginFabrique.h"

class QPortIO;
class QPluginListWidged : public QListWidget
{
    Q_OBJECT
    
public:
    explicit QPluginListWidged( QWidget *parent = 0, InterfaceType_t  type = UNDEFINED );
    ~QPluginListWidged();
    PluginDescription getSelectedPlugin();
protected:
    void addToList( PluginDescription& desc );
public slots:
    void reloadPLuginList();

private:
    QList< PluginDescription > m_Plugins;
    InterfaceType_t mType;
};

#endif // QFRAIOPORTSVIEW_H
