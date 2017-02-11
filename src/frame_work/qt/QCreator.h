#ifndef _QCREATOR_H
#define _QCREATOR_H


#include "base/global.h"
#include <QObject>

#include "base/CCreator.h"

class FRAME_WORKSHARED_EXPORT QCreator : public QObject, public CCreator {
Q_OBJECT

  public:
    explicit QCreator(QObject * parent = NULL);

    virtual ~QCreator();

    virtual void Free();

};
#endif
