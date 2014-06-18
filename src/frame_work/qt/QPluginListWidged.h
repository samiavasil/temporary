#ifndef QPLUGINLISTWIDGED_H
#define QPLUGINLISTWIDGED_H

#include <QWidget>
#include <QTableWidget>
#include "qt/QPluginFabrique.h"
#include "qt/QpluginFilter.h"

class QPortIO;
class QPluginListWidged : public QTableWidget
{
    Q_OBJECT
    
public:
    typedef enum{
       LIS
    }cfg_type_t;

    explicit QPluginListWidged( QWidget *parent = 0, const QpluginFilter& filter = QpluginFilter() );
    ~QPluginListWidged();
    PluginDescription getSelectedPlugin();
    void setFilter( const QpluginFilter& filter );

protected:
    void addToList( PluginDescription& desc );
public slots:
    void reloadPLuginList();
protected slots:
    void OnitemChanged(QTableWidgetItem*item);
signals:
    void enablePlugin( PluginDescription, bool );
private:
    QList< PluginDescription > m_Plugins;
    QpluginFilter m_Filter;
};

#endif // QFRAIOPORTSVIEW_H
