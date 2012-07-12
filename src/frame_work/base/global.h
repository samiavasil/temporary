#ifndef __GLOBAL_H__
#define __GLOBAL_H__
typedef long long int int64;

enum{
	NO_ERR,
    WRONG_PARAMS,
    WRONG_DATA,
    NULL_POINTER,
    SOME_ERROR
};

/*TODO: FIX ME*/
#include  <QtGlobal>
#define DEBUG    qDebug
#define CRITICAL qCritical
#define FATAL    qFatal

#endif
