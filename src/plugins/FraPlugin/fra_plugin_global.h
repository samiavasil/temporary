#ifndef FRA_PLUGIN_GLOBAL_H
#define FRA_PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEVICE_FACTORY_PLUGIN_LIBRARY)
#  define FRA_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#  define FRA_PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // FRAME_WORK_GLOBAL_H

