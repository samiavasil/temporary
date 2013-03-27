#ifndef _QCREATOR_H
#define _QCREATOR_H


#include <QObject>

#include "base/CCreator.h"

class QCreator : public QObject, public CCreator {
  public:
    explicit QCreator(QObject * parent = NULL);
};
#endif
