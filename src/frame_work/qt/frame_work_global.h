#ifndef FRAME_WORK_GLOBAL_H
#define FRAME_WORK_GLOBAL_H
#include "base/global.h"
#include <QtCore/qglobal.h>

#if defined(FRAME_WORK_LIBRARY)
#  define FRAME_WORKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FRAME_WORKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FRAME_WORK_GLOBAL_H
