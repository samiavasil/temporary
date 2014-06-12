#ifndef QPLUGINFILTER_H
#define QPLUGINFILTER_H

#include "qt/PluginDescription.h"
#include "qt/QPluginFabrique.h"

class QpluginFilter
{
public:
    QpluginFilter( );
    QpluginFilter( InterfaceType_t  type );

    QpluginFilter( PluginDescription& desc  );

    bool filtered( QPluginFabrique &fab ) const;

protected:
    PluginDescription m_filterDesc;
};

#endif // QPLUGINFILTER_H
