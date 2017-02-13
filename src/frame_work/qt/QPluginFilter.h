#ifndef QPLUGINFILTER_H
#define QPLUGINFILTER_H

#include "qt/PluginDescription.h"
#include "qt/QPluginFactory.h"

class Q_DECL_EXPORT QPluginFilter
{
public:
    QPluginFilter( );
    QPluginFilter( InterfaceType_t  type );

    QPluginFilter( PluginDescription& desc  );

    bool filtered( QPluginFactory &fab ) const;

protected:
    PluginDescription m_filterDesc;
};

#endif // QPLUGINFILTER_H
