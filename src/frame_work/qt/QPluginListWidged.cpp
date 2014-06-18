#include "base/global.h"
#include "QPluginListWidged.h"
#include "qt/QPluginList.h"
#include<QHeaderView>

#define LOCATION_COLUMN 2
QPluginListWidged::QPluginListWidged( QWidget *parent, const QpluginFilter &filter ):QTableWidget(parent),m_Filter(filter)

{
    setColumnCount(3);
    //TODO: connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,this, SLOT(reloadPLuginList()) );
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(OnitemChanged(QTableWidgetItem*)) );
    connect(this,SIGNAL(enablePlugin(PluginDescription,bool)),this,SLOT(enPlugin(PluginDescription,bool)) );
    horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    reloadPLuginList();
}

QPluginListWidged::~QPluginListWidged()
{

}

void QPluginListWidged::reloadPLuginList(){

    m_Plugins = QPluginList::Instance()->getAllPlugins( QpluginFilter( m_Filter ) );
    blockSignals( true );
    model()->removeRows(0, rowCount());

    foreach( PluginDescription desc, m_Plugins ){
    int count = rowCount();
       insertRow( count );
       QTableWidgetItem *item = new QTableWidgetItem( desc.name() );
       if( !desc.icon().isNull() ){
           QIcon icon = desc.icon();
           item->setIcon( icon );
       }
       item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       setItem( count, 0, item );

       item = new QTableWidgetItem(desc.category());
       item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       setItem( count, 1, item );

       item = new QTableWidgetItem( desc.location() );
       item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
       if( desc.is_enabled()  ){
         item->setCheckState ( Qt::Checked );
       }
       else{
         item->setCheckState ( Qt::Unchecked );
       }
       setItem( count, LOCATION_COLUMN, item );

       m_Plugins.append(desc);
     }
    blockSignals( false );
}

PluginDescription  QPluginListWidged::getSelectedPlugin(){
   return m_Plugins.value( currentRow(), PluginDescription() );
}

void QPluginListWidged::OnitemChanged( QTableWidgetItem* item ){
  if( item ){
      int r = row( item  );
      int c =column( item  );
      if( r != -1  && c == LOCATION_COLUMN ){
          emit enablePlugin( m_Plugins.value( r, PluginDescription() ), Qt::Checked == item->checkState() );
      }
  }
}

void QPluginListWidged::setFilter( const QpluginFilter& filter ){
    m_Filter = filter;
    reloadPLuginList();
}
