#include "base/global.h"
#include "QPluginListWidget.h"
#include "qt/QPluginList.h"
#include "qt/QPluginViewProperty.h"
#include<QHeaderView>
#include<QMenu>

#define ENABLE_COLUMN      (0)
#define NAME_COLUMN        (1)
#define CATEGORY_COLUMN    (2)
#define TYPE_COLUMN        (3)
#define LOCATION_COLUMN    (4)
#define DESCRIPTION_COLUMN (5)
#define VERSION_COLUMN     (6)

const char* col_name[7]={
   "ENABLE",
   "NAME",
   "CATEGORY",
   "TYPE",
   "LOCATION",
   "DESCRIPTION",
   "VERSION",
};

cfgViewTypeT::cfgViewTypeT(){
   cfg.value        = 0;
   name(true);
}

cfgViewTypeT& cfgViewTypeT::operator= ( const cfgViewTypeT& in ){
   bool hideDisabled    = cfg.bit.hideDisabled;
   cfg.value            = in.cfg.value;
   cfg.bit.hideDisabled = hideDisabled;
   return *this;
}

cfgViewTypeT& cfgViewTypeT::type(bool in){
   cfg.bit.type = in;
   return *this;
}
cfgViewTypeT& cfgViewTypeT::location(bool in){
   cfg.bit.location = in;
   return *this;
}
cfgViewTypeT& cfgViewTypeT::name(bool in){
    cfg.bit.name = in;
    return *this;
}
cfgViewTypeT& cfgViewTypeT::category(bool in){
    cfg.bit.category = in;
    return *this;
}
cfgViewTypeT& cfgViewTypeT::version(bool in){
    cfg.bit.version = in;
    return *this;
}
cfgViewTypeT& cfgViewTypeT::description(bool in){
    cfg.bit.description = in;
    return *this;
}
cfgViewTypeT& cfgViewTypeT::icon(bool in){
   cfg.bit.icon = in;
   return *this;
}
cfgViewTypeT& cfgViewTypeT::enable(bool in){
   cfg.bit.enable = in;
   return *this;
}

cfgViewTypeT& cfgViewTypeT::hideDisabled(bool in){
    cfg.bit.hideDisabled = in;
    return *this;
}

bool cfgViewTypeT::type() const{
   return cfg.bit.type;
}

bool cfgViewTypeT::location() const{
   return cfg.bit.location;
}

bool cfgViewTypeT::name() const{
   return cfg.bit.name;
}

bool cfgViewTypeT::category() const{
   return cfg.bit.category;
}

bool cfgViewTypeT::version() const{
   return cfg.bit.version;
}

bool cfgViewTypeT::description() const{
   return cfg.bit.description;
}

bool cfgViewTypeT::icon()  const{
   return cfg.bit.icon;
}
bool cfgViewTypeT::enable()const{
   return cfg.bit.enable;
}

bool cfgViewTypeT::hideDisabled() const{
   return cfg.bit.hideDisabled;
}


QPluginListWidget::QPluginListWidget( QWidget *parent, const QpluginFilter &filter, const cfgViewTypeT& viewType  ):
                                      QTableWidget(parent),m_Filter(filter),m_ViewType(viewType)

{
    QStringList  labels;
    m_ConnToCheck = 0;
    setColumnCount( 7 );
    setSortingEnabled(true);
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(OnitemChanged(QTableWidgetItem*)) );
    connect(this,SIGNAL( activated(QModelIndex)),this,SLOT(OnItemActivated(QModelIndex)) );

    for( int i=0; i<7; i++ ){
        labels.append(col_name[i]);
    }
    setHorizontalHeaderLabels(labels);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    addContextMenu();
    reloadPLuginList();

}


void QPluginListWidget::currentChanged(const QModelIndex &current, const QModelIndex &previous){
    QTableWidget::currentChanged( current, previous );
    if( current.row() != previous.row() ){
       emit selectedPluginChanged(  m_Plugins.value( current.row(), PluginDescription() ) );
    }
}

QPluginListWidget::~QPluginListWidget()
{

}


void QPluginListWidget::reloadPLuginList(){

    m_Plugins = QPluginList::Instance()->getAllPlugins( QpluginFilter( m_Filter ) );
    blockSignals( true );
    model()->removeRows(0, rowCount());
    RightVisibleCol = 0;
    showCol( NAME_COLUMN       , m_ViewType.name());
    showCol( CATEGORY_COLUMN   , m_ViewType.category());
    showCol( TYPE_COLUMN       , m_ViewType.type());
    showCol( LOCATION_COLUMN   , m_ViewType.location());
    showCol( DESCRIPTION_COLUMN, m_ViewType.description());
    showCol( VERSION_COLUMN    , m_ViewType.version());
    showCol( ENABLE_COLUMN     , m_ViewType.enable());
    horizontalHeader()->setResizeMode(RightVisibleCol, QHeaderView::Stretch );

    foreach( PluginDescription desc, m_Plugins ){

       if( !( m_ViewType.hideDisabled() && !desc.is_enabled() ) ){
           int count = rowCount();
           insertRow( count );
           QTableWidgetItem *item = new QTableWidgetItem( desc.name() );
           if( m_ViewType.icon() && !desc.icon().isNull() ){
               QIcon icon = desc.icon();
               item->setIcon( icon );
           }
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, NAME_COLUMN, item );

           item = new QTableWidgetItem(desc.category());
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, CATEGORY_COLUMN, item );

           item = new QTableWidgetItem( QString("%1").arg(desc.type()) );
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, TYPE_COLUMN, item );

           item = new QTableWidgetItem( desc.location() );
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, LOCATION_COLUMN, item );

           item = new QTableWidgetItem(desc.description());
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, DESCRIPTION_COLUMN, item );

           item = new QTableWidgetItem(desc.version());
           item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
           setItem( count, VERSION_COLUMN, item );

           item = new QTableWidgetItem();

           if( m_ConnToCheck > 0 ){
              item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
           }
           else{
              item->setFlags(Qt::ItemIsUserCheckable);
           }

           if( desc.is_enabled() ){
             item->setCheckState ( Qt::Checked );
           }
           else{
             item->setCheckState ( Qt::Unchecked );
           }

           setItem( count, ENABLE_COLUMN, item );
           m_Plugins.append(desc);
       }
     }
    blockSignals( false );
    emit selectedPluginChanged(  m_Plugins.value( currentRow(), PluginDescription() ) );
}

PluginDescription  QPluginListWidget::getSelectedPlugin(){
   return m_Plugins.value( currentRow(), PluginDescription() );
}

const QList< PluginDescription >& QPluginListWidget::getPluginList(){
    return m_Plugins;
}

void QPluginListWidget::OnitemChanged( QTableWidgetItem* item ){
  if( item ){
      int r = row( item  );
      int c =column( item  );
      if( r != -1  && c == ENABLE_COLUMN ){
          emit enablePlugin( m_Plugins.value( r, PluginDescription() ), Qt::Checked == item->checkState() );
      }
  }
}

void QPluginListWidget::setFilter( const QpluginFilter& filter ){
    m_Filter = filter;
    reloadPLuginList();
}

void QPluginListWidget::updateVisibility(){
///TODO
}

void QPluginListWidget::addContextMenu(){
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(ShowContextMenu(const QPoint&)));
}

void QPluginListWidget::ShowContextMenu( const QPoint& pos ){
    // for most widgets
    QPoint globalPos = mapToGlobal(pos);
    QMenu myMenu;
    QAction* action  = new QAction( "Some Option Here",&myMenu );
    myMenu.addAction( action );
    action  = new QAction( "Properties",&myMenu );
    connect( action, SIGNAL(triggered()), this,SLOT(ShowProperties()) );
    myMenu.addAction( action );
    myMenu.exec( globalPos );
     reloadPLuginList();
}

void QPluginListWidget::ShowProperties( ){
    QPluginViewProperty prop( m_ViewType );
    prop.exec();
    m_ViewType = prop.getProperties();
    updateVisibility();
}

void QPluginListWidget::showCol( int col, bool show ){
    if( show ){
       showColumn( col );
       horizontalHeader()->setResizeMode( col, QHeaderView::Interactive );
       if( col > RightVisibleCol ){
           RightVisibleCol = col;
       }
    }
    else{
       hideColumn( col );
    }
}

void QPluginListWidget::connectNotify ( const char * signal ){
    const char* ptr = SIGNAL(enablePlugin(PluginDescription,bool));
    if( !strcmp( signal, ptr )  ){
        m_ConnToCheck = 100;
        QObject::connectNotify (signal);
        reloadPLuginList();
    }
}
