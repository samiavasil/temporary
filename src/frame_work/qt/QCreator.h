#ifndef _QCREATOR_H
#define _QCREATOR_H


#include <QObject>

#include "base/CCreator.h"

class QCreator : public QObject, public CCreator {
  public:
    explicit QCreator(QObject * parent = NULL);
    virtual void Create( CFrameWork * fW) = 0;
    virtual void Free() = 0;
};
#endif
