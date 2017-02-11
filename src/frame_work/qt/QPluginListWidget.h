#ifndef QPLUGINLISTWIDGED_H
#define QPLUGINLISTWIDGED_H

#include <QWidget>
#include <QTableWidget>
#include "qt/QPluginFabrique.h"
#include "qt/QpluginFilter.h"
#include"base/global.h"

#define ADD_BIT(x)  unsigned int x :1;
class FRAME_WORKSHARED_EXPORT cfgViewTypeT{
public:

    cfgViewTypeT();
    cfgViewTypeT& type(bool in);
    cfgViewTypeT& location(bool in);
    cfgViewTypeT& name(bool in);
    cfgViewTypeT& category(bool in);
    cfgViewTypeT& version(bool in);
    cfgViewTypeT& description(bool in);
    cfgViewTypeT& icon(bool in);
    cfgViewTypeT& enable(bool in);
    cfgViewTypeT& hideDisabled(bool in);

    bool type()         const;
    bool location()     const;
    bool name()         const;
    bool category()     const;
    bool version()      const;
    bool description()  const;
    bool icon()         const;
    bool enable()       const;
    bool hideDisabled() const;

    cfgViewTypeT& operator= (const cfgViewTypeT&);
protected:
    typedef union{
       struct bit_{
           ADD_BIT(type)
           unsigned int location     :1;
           unsigned int name         :1;
           unsigned int category     :1;
           unsigned int version      :1;
           unsigned int description  :1;
           unsigned int icon         :1;
           unsigned int enable       :1;
           unsigned int hideDisabled :1;
       }bit;
       unsigned int value;
    }intDataT;
    intDataT cfg;
};

class QPortIO;
class FRAME_WORKSHARED_EXPORT QPluginListWidget : public QTableWidget
{
    Q_OBJECT
    
public:
    explicit QPluginListWidget( QWidget *parent = 0, const QpluginFilter& filter = QpluginFilter(),
                                const cfgViewTypeT& viewType = cfgViewTypeT() );
    ~QPluginListWidget();
    PluginDescription getSelectedPlugin();
    const QList< PluginDescription >& getPluginList();
    void setFilter( const QpluginFilter& filter );
    void setViewType( const cfgViewTypeT& viewType );
    const QpluginFilter& filter();
    const cfgViewTypeT&  viewType();

protected:
    void addToList( PluginDescription& desc );
    void showCol( int col, bool show);
    void addContextMenu();
    void updateVisibility();
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
void connectNotify ( const char * signal );
#else
void connectNotify (const QMetaMethod & signal);
#endif
public slots:
    void reloadPLuginList();
    void ShowContextMenu(const QPoint& pos);
    void ShowProperties( );
protected slots:
    void OnitemChanged(QTableWidgetItem*item);
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
signals:
    void enablePlugin( PluginDescription, bool );
    void selectedPluginChanged( const PluginDescription& );
    void rereadPLuginList();
private:
    QList< PluginDescription > m_Plugins;
    QpluginFilter m_Filter;
    cfgViewTypeT m_ViewType;
    int RightVisibleCol;
    int m_ConnToCheck;
};

#endif // QFRAIOPORTSVIEW_H
