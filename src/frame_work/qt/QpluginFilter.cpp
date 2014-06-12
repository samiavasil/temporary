#include "QpluginFilter.h"

QpluginFilter::QpluginFilter()
{
    m_filterDesc = PluginDescription();
}


QpluginFilter::QpluginFilter( InterfaceType_t type ){
    m_filterDesc = PluginDescription(type);
}

QpluginFilter::QpluginFilter( PluginDescription& desc  ){
    m_filterDesc = desc;
}

bool QpluginFilter::filtered( QPluginFabrique &fab ) const{
    return m_filterDesc.compare_by_valid_fields( fab.getDescription() );
}
