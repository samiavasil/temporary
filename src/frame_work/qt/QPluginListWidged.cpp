#include "base/global.h"
#include "QPluginListWidged.h"
#include "qt/QPluginList.h"

QPluginListWidged::QPluginListWidged(QWidget *parent, InterfaceType_t type) :QListWidget(parent),mType(type)

{
    connect( QPluginList::Instance(),SIGNAL(pluginsUpdate()) ,this, SLOT(reloadPLuginList()) );
    reloadPLuginList();
}

QPluginListWidged::~QPluginListWidged()
{

}

class gpWidget:public QWidget
{
public:
    gpWidget(QWidget* parent=NULL):QWidget(parent)
    {

    }
    ~gpWidget()
    {
        DEBUG << "destroy  gpWidget"<<endl;
    }
};

void QPluginListWidged::reloadPLuginList(){
    QList<PluginDescription>  list = QPluginList::Instance()->getAllActivePlugins( mType );
    blockSignals( true );
    clear();
    m_Plugins.clear();
    foreach( PluginDescription desc, list ){
        if( mType == UNDEFINED || mType == desc.type() ){
            if( !m_Plugins.contains( desc ) ){
                addItem( desc.name() );
                m_Plugins.append(desc);
            }
        }
    }
    blockSignals( false );
}

PluginDescription  QPluginListWidged::getSelectedPlugin(){
   return m_Plugins.value( currentRow(), PluginDescription() );
}
