#include "QPluginFilter.h"

QPluginFilter::QPluginFilter()
{
    m_filterDesc = PluginDescription();
}


QPluginFilter::QPluginFilter( InterfaceType_t type ){
    m_filterDesc = PluginDescription(type);
}

QPluginFilter::QPluginFilter( PluginDescription& desc  ){
    m_filterDesc = desc;
}

bool QPluginFilter::filtered( QPluginFactory &fab ) const{
    return m_filterDesc.compare_by_valid_fields( fab.getDescription() );
}
